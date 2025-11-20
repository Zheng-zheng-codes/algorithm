/*
题目描述
如题，已知一个数列，你需要进行下面三种操作：
将某区间每一个数乘上 x；
将某区间每一个数加上 x；
求出某区间每一个数的和。
输入格式
第一行包含三个整数 n,q,m，分别表示该数列数字的个数、操作的总个数和模数。
第二行包含 n 个用空格分隔的整数，其中第 i 个数字表示数列第 i 项的初始值。
接下来 q 行每行包含若干个整数，表示一个操作，具体如下：
操作 1： 格式：1 x y k 含义：将区间 [x,y] 内每个数乘上 k。
操作 2： 格式：2 x y k 含义：将区间 [x,y] 内每个数加上 k。
操作 3： 格式：3 x y 含义：输出区间 [x,y] 内每个数的和对 m 取模所得的结果。
输出格式
输出包含若干行整数，即为所有操作 3 的结果。
*/
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
int mod;
struct tree
{
    int sum;
    int addlz;
    int mulz;
    tree(){addlz=0;mulz=1;}
}t[maxn<<2];
int a[maxn];
void pushup(int k)
{
    t[k].sum=(t[ls].sum+t[rs].sum)%mod;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].sum=a[l]%mod;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
void putadd(int k,int l,int r,int val)
{
    val%=mod;
    t[k].sum+=(r-l+1)*val;
    t[k].sum%=mod;
    t[k].addlz+=val;
    t[k].addlz%=mod;
}
void putmu(int k,int l,int r,int val)
{
    val%=mod;
    t[k].sum*=val;
    t[k].sum%=mod;
    t[k].mulz*=val;
    t[k].mulz%=mod;
    t[k].addlz*=val;
    t[k].addlz%=mod;
}
void pushdown(int k,int l,int r)
{
    int mid=l+r>>1;
    if(t[k].mulz!=1)
    {
        putmu(ls,l,mid,t[k].mulz);
        putmu(rs,mid+1,r,t[k].mulz);
        t[k].mulz=1;
    }
    if(t[k].addlz)
    {
        putadd(ls,l,mid,t[k].addlz);
        putadd(rs,mid+1,r,t[k].addlz);
        t[k].addlz=0;
    }
}
void add(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        putadd(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)add(ls,l,mid,p,q,val);
    else if(p>mid)add(rs,mid+1,r,p,q,val);
    else add(ls,l,mid,p,mid,val),add(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
void mu(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        putmu(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)mu(ls,l,mid,p,q,val);
    else if(p>mid)mu(rs,mid+1,r,p,q,val);
    else mu(ls,l,mid,p,mid,val),mu(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    int mid=l+r>>1;
    pushdown(k,l,r);
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return (query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q))%mod;
    pushup(k);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m>>mod;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    for(int i=0;i<m;i++)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1)
        {
            int k;
            cin>>k;
            mu(1,1,n,x,y,k);
        }
        else if(op==2)
        {
            int k;
            cin>>k;
            add(1,1,n,x,y,k);
        }
        else cout<<query(1,1,n,x,y)%mod<<'\n';
    }
    return 0;
}
