/*
题目描述
如题，已知一个数列 {ai}，你需要进行下面两种操作：将某区间每一个数加上 k。求出某区间每一个数的和。
输入格式
第一行包含两个整数 n,m，分别表示该数列数字的个数和操作的总个数。
第二行包含 n 个用空格分隔的整数 ai，其中第 i个数字表示数列第 i项的初始值。
接下来 m 行每行包含 3 或 4 个整数，表示一个操作，具体如下：
1 x y k：将区间 [x,y] 内每个数加上 k。
2 x y：输出区间 [x,y] 内每个数的和。
输出格式
输出包含若干行整数，即为所有操作 2 的结果。
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
struct tree
{
    int sum;
    int lz;//懒标记
    tree(){lz=0;}
}t[maxn<<2];
int a[maxn];
//当左右两侧都结束后将信息返回上一层
void pushup(int k)
{
    t[k].sum=t[ls].sum+t[rs].sum;
}
//建立线段树
//k:当前位置  l、r:当前的区间
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].sum=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
//放懒标记
void puttag(int k,int l,int r,int val)
{
    t[k].sum+=val*(r-l+1);
    t[k].lz+=val;
}
//如果遇见有懒标记的点将懒标记传给下一层
void pushdown(int k,int l,int r)
{
    if(t[k].lz)
    {
        int mid=l+r>>1;
        puttag(ls,l,mid,t[k].lz);
        puttag(rs,mid+1,r,t[k].lz);
        t[k].lz=0;
    }
}
//范围查询
//k:当前位置  l、r:当前的区间   p、q：查询的区间
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q);
}
//范围修改
//k:当前位置  l、r:当前的区间   p、q：更改的区间  val：更改的值
void modify(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        puttag(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify(ls,l,mid,p,q,val);
    else if(p>mid)modify(rs,mid+1,r,p,q,val);
    else modify(ls,l,mid,p,mid,val),modify(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1)
        {
            int k;
            cin>>k;
            modify(1,1,n,x,y,k);
        }
        else cout<<query(1,1,n,x,y)<<'\n';
    }
    return 0;
}
