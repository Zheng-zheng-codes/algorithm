/*
题目描述
lxhgww 最近收到了一个 01 序列，序列里面包含了 n 个数，下标从 0 开始。
这些数要么是 0，要么是 1，现在对于这个序列有五种变换操作和询问操作：
0 l r 把 [l,r] 区间内的所有数全变成 0；
1 l r 把 [l,r] 区间内的所有数全变成 1；
2 l r 把 [l,r] 区间内的所有数全部取反，也就是说把所有的 0 变成 1，把所有的 1 变成 0；
3 l r 询问 [l,r] 区间内总共有多少个 1；
4 l r 询问 [l,r] 区间内最多有多少个连续的 1。
对于每一种询问操作，lxhgww 都需要给出回答，聪明的程序员们，你们能帮助他吗？
输入格式
第一行两个正整数 n,m，表示序列长度与操作个数。
第二行包括 n 个数，表示序列的初始状态。
接下来 m 行，每行三个整数，表示一次操作。
输出格式
对于每一个询问操作，输出一行一个数，表示其对应的答案。
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
struct tree
{
    int len;
    int pre0;
    int suf0;
    int pre1;
    int suf1;
    int long1;
    int long0;
    int lz1;//有没有覆盖操作
    int lz2;//有没有取反操作
    tree(){lz1=-1;lz2=0;}
}t[maxn<<2];
int a[maxn];
void pushup(int k,int l,int r)
{
    t[k].len=t[ls].len+t[rs].len;
    int mid=l+r>>1;
    t[k].pre0 = (t[ls].pre0 == mid - l + 1) ? t[ls].pre0 + t[rs].pre0 : t[ls].pre0;
    t[k].suf0 = (t[rs].suf0 == r - mid) ? t[rs].suf0 + t[ls].suf0 : t[rs].suf0;
    t[k].pre1 = (t[ls].pre1 == mid - l + 1) ? t[ls].pre1 + t[rs].pre1 : t[ls].pre1;
    t[k].suf1 = (t[rs].suf1 == r - mid) ? t[rs].suf1 + t[ls].suf1 : t[rs].suf1;
    t[k].long1=max(max(t[ls].long1,t[rs].long1),t[ls].suf1+t[rs].pre1);
    t[k].long0=max(max(t[ls].long0,t[rs].long0),t[ls].suf0+t[rs].pre0);
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].len=a[l];
        if(a[l]==0)t[k].pre0=1,t[k].pre1=0,t[k].suf0=1,t[k].suf1=0,t[k].long1=0,t[k].long0=1;
        else t[k].pre0=0,t[k].pre1=1,t[k].suf0=0,t[k].suf1=1,t[k].long1=1,t[k].long0=0;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k,l,r);
}
//放覆盖的懒标记
void puttag1(int k,int l,int r,int val)
{
    t[k].lz2=0;
    if(val)t[k].len=r-l+1,t[k].pre1=r-l+1,t[k].suf1=r-l+1,
    t[k].pre0=0,t[k].suf0=0,t[k].long1=r-l+1,t[k].long0=0;
    else t[k].len=0,t[k].pre1=0,t[k].suf1=0,
    t[k].pre0=r-l+1,t[k].suf0=r-l+1,t[k].long1=0,t[k].long0=r-l+1;
    t[k].lz1=val;
}
//放取反懒标记
void puttag2(int k,int l,int r)
{
    if(t[k].lz1!=-1)
    {
        if(t[k].lz1==0)t[k].lz1=1;
        else t[k].lz1=0;
    }
    int tmp=r-l+1;
    t[k].len=tmp-t[k].len;
    swap(t[k].pre0,t[k].pre1);
    swap(t[k].suf0,t[k].suf1);
    swap(t[k].long0,t[k].long1);
    if(t[k].lz2)t[k].lz2=0;
    else t[k].lz2=1;
}
void pushdown(int k,int l,int r)
{
    if(t[k].lz2)
    {
        int mid=l+r>>1;
        puttag2(ls,l,mid);
        puttag2(rs,mid+1,r);
        t[k].lz2=0;
    }
    if(t[k].lz1!=-1)
    {
        int mid=l+r>>1;
        puttag1(ls,l,mid,t[k].lz1);
        puttag1(rs,mid+1,r,t[k].lz1);
        t[k].lz1=-1;
    }
}
void modify1(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        puttag1(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify1(ls,l,mid,p,q,val);
    else if(p>mid)modify1(rs,mid+1,r,p,q,val);
    else modify1(ls,l,mid,p,mid,val),modify1(rs,mid+1,r,mid+1,q,val);
    pushup(k,l,r);
}
void modify2(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)
    {
        puttag2(k,l,r);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify2(ls,l,mid,p,q);
    else if(p>mid)modify2(rs,mid+1,r,p,q);
    else modify2(ls,l,mid,p,mid),modify2(rs,mid+1,r,mid+1,q);
    pushup(k,l,r);
}
int query1(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].len;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query1(ls,l,mid,p,q);
    else if(p>mid)return query1(rs,mid+1,r,p,q);
    else return query1(ls,l,mid,p,mid)+query1(rs,mid+1,r,mid+1,q);
}
int query2(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].long1;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query2(ls,l,mid,p,q);
    else if(p>mid)return query2(rs,mid+1,r,p,q);
    else 
    {
        int num1=query2(ls,l,mid,p,mid);
        int num2=query2(rs,mid+1,r,mid+1,q);
        int tmp1=min(mid-p+1,t[ls].suf1);
        int tmp2=min(q-mid,t[rs].pre1);
        return max(max(num1,num2),tmp1+tmp2);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==0)modify1(1,1,n,x+1,y+1,0);
        else if(op==1)modify1(1,1,n,x+1,y+1,1);
        else if(op==2)modify2(1,1,n,x+1,y+1);
        else if(op==3)cout<<query1(1,1,n,x+1,y+1)<<'\n';
        else cout<<query2(1,1,n,x+1,y+1)<<'\n';
    }
    return 0;
}