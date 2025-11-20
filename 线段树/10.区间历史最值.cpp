/*
题目描述
给出一个长度为 n 的数列 A，同时定义一个辅助数组 B，B 开始与 A 完全相同。接下来进行了 m 次操作，
操作有五种类型，按以下格式给出：
1 l r k：对于所有的 i∈[l,r]，将 Ai加上 k（k 可以为负数）。
2 l r v：对于所有的 i∈[l,r]，将 Ai变成 min(Ai,v)。
3 l r：Ai从l到r的和。
4 l r：对于所有的 i∈[l,r]，求 Ai的最大值。
5 l r：对于所有的 i∈[l,r]，求 Bi的最大值。
在每一次操作后，我们都进行一次更新，让 Bi←max(Bi,Ai)。
输入格式
第一行包含两个正整数 n,m，分别表示数列 A 的长度和操作次数。
第二行包含 n 个整数 A1,A2,⋯,An，表示数列 A。
接下来 m 行，每行行首有一个整数 op，表示操作类型；接下来两个或三个整数表示操作参数，格式见【题目描述】。
输出格式
对于 op∈{3,4,5} 的操作，输出一行包含一个整数，表示这个询问的答案。
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
const int maxn=5e5+10;
const int minn=LLONG_MIN;
struct tree
{
    int mam;//最大值
    int sem;//次大值
    int num;//最大值个数
    int sum;//累加和
    int maxhis;//历史最大值
    int maxadd;//最大值增幅（懒标记）
    int otheradd;//其他值增幅（懒标记）
    int maxaddtop;//最大值的最大增幅（懒标记）
    int otheraddtop;//其他值的最大增幅（懒标记）
    tree(){maxadd=0;otheradd=0;maxaddtop=0;otheraddtop=0;}
}t[maxn<<2];
int a[maxn];
void pushup(int k)
{
    t[k].sum=t[ls].sum+t[rs].sum;
    t[k].mam=max(t[ls].mam,t[rs].mam);
    t[k].maxhis=max(t[ls].maxhis,t[rs].maxhis);
    if(t[ls].mam>t[rs].mam)
    {
        t[k].num=t[ls].num;
        t[k].sem=max(t[ls].sem,t[rs].mam);
    }
    else if(t[ls].mam<t[rs].mam)
    {
        t[k].num=t[rs].num;
        t[k].sem=max(t[ls].mam,t[rs].sem);
    }
    else 
    {
        t[k].num=t[ls].num+t[rs].num;
        t[k].sem=max(t[ls].sem,t[rs].sem);
    }
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].mam=a[l];
        t[k].sem=minn;
        t[k].num=1;
        t[k].sum=a[l];
        t[k].maxhis=a[l];
        t[k].maxadd = t[k].otheradd = t[k].maxaddtop = t[k].otheraddtop = 0;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
void puttag(int k,int l,int r,int maxadd,int otheradd,int maxaddtop,int otheraddtop)
//参数对应了四个懒标记
{
    t[k].maxhis=max(t[k].maxhis,t[k].mam+maxaddtop);
    t[k].maxaddtop=max(t[k].maxaddtop,t[k].maxadd+maxaddtop);
    t[k].otheraddtop=max(t[k].otheraddtop,t[k].otheradd+otheraddtop);
    t[k].mam+=maxadd;
    t[k].sum+=(r-l+1-t[k].num)*otheradd+t[k].num*maxadd;
    if(t[k].sem!=minn)t[k].sem+=otheradd;
    t[k].maxadd+=maxadd;
    t[k].otheradd+=otheradd;
}
void pushdown(int k,int l,int r)
{
    int mid=l+r>>1;
    //注意这里不能和t[k].mam比，因为懒标记还没有下发所以应该和左右结点最大值比
    int temp=max(t[ls].mam,t[rs].mam);
    if(t[ls].mam==temp)puttag(ls,l,mid,t[k].maxadd,t[k].otheradd,t[k].maxaddtop,t[k].otheraddtop);
    else puttag(ls,l,mid,t[k].otheradd,t[k].otheradd,t[k].otheraddtop,t[k].otheraddtop);
    if(t[rs].mam==temp)puttag(rs,mid+1,r,t[k].maxadd,t[k].otheradd,t[k].maxaddtop,t[k].otheraddtop);
    else puttag(rs,mid+1,r,t[k].otheradd,t[k].otheradd,t[k].otheraddtop,t[k].otheraddtop);
    t[k].maxadd=0;
    t[k].otheradd=0;
    t[k].maxaddtop=0;
    t[k].otheraddtop=0;
}
void minset(int k,int l,int r,int p,int q,int v)
{
    if(v>=t[k].mam)return;
    if(l==p&&r==q&&v>t[k].sem)
    {
        puttag(k,l,r,v-t[k].mam,0,v-t[k].mam,0);
        return;
    }
    int mid=l+r>>1;
    pushdown(k,l,r);
    if(q<=mid)minset(ls,l,mid,p,q,v);
    else if(p>mid)minset(rs,mid+1,r,p,q,v);
    else minset(ls,l,mid,p,mid,v),minset(rs,mid+1,r,mid+1,q,v);
    pushup(k);
}
void add(int k,int l,int r,int p,int q,int v)
{
    if(l==p&&r==q)
    {
        puttag(k,l,r,v,v,v,v);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)add(ls,l,mid,p,q,v);
    else if(p>mid)add(rs,mid+1,r,p,q,v);
    else add(ls,l,mid,p,mid,v),add(rs,mid+1,r,mid+1,q,v);
    pushup(k);
}
//查询累加和
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q);
}
//查询最大值
int query2(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].mam;
    int mid=l+r>>1;
    pushdown(k,l,r);
    if(q<=mid)return query2(ls,l,mid,p,q);
    else if(p>mid)return query2(rs,mid+1,r,p,q);
    else return max(query2(ls,l,mid,p,mid),query2(rs,mid+1,r,mid+1,q));
}
//查询历史最大值
int query3(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].maxhis;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query3(ls,l,mid,p,q);
    else if(p>mid)return query3(rs,mid+1,r,p,q);
    else return max(query3(ls,l,mid,p,mid),query3(rs,mid+1,r,mid+1,q));
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1)
        {
            int k;
            cin>>k;
            add(1,1,n,l,r,k);
        }
        else if(op==2)
        {
            int v;
            cin>>v;
            minset(1,1,n,l,r,v);
        }
        else if(op==3)cout<<query(1,1,n,l,r)<<'\n';
        else if(op==4)cout<<query2(1,1,n,l,r)<<'\n';
        else cout<<query3(1,1,n,l,r)<<'\n';
    }
    return 0;
}