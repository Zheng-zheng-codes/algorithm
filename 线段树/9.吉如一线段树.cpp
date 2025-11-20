/*
给定一个长度为n的数组arr，实现支持以下三种操作的结构
操作 0 l r x : 把arr[l..r]范围的每个数v，更新成min(v, x)
操作 1 l r   : 查询arr[l..r]范围上的最大值
操作 2 l r   : 查询arr[l..r]范围上的累加和
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
const int maxn=1e6+10;
const int minn=-1;
struct tree
{
    int mam;//最大值
    int sem;//次大值
    int num;//最大值个数
    int sum;//累加和
}t[maxn<<2];
int a[maxn];
void pushup(int k)
{
    t[k].sum=t[ls].sum+t[rs].sum;
    t[k].mam=max(t[ls].mam,t[rs].mam);
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
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
void puttag(int k,int v)
{
    if(v<t[k].mam)
    {
        t[k].sum-=t[k].num*(t[k].mam-v);
        t[k].mam=v;
    }
}
void pushdown(int k)
{
    puttag(ls,t[k].mam);
    puttag(rs,t[k].mam);
}
void minset(int k,int l,int r,int p,int q,int v)
{
    if(v>=t[k].mam)return;
    if(l==p&&r==q&&v>t[k].sem)
    {
        puttag(k,v);
        return;
    }
    int mid=l+r>>1;
    pushdown(k);
    if(q<=mid)minset(ls,l,mid,p,q,v);
    else if(p>mid)minset(rs,mid+1,r,p,q,v);
    else minset(ls,l,mid,p,mid,v),minset(rs,mid+1,r,mid+1,q,v);
    pushup(k);
}
//查询累加和
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    pushdown(k);
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
    pushdown(k);
    if(q<=mid)return query2(ls,l,mid,p,q);
    else if(p>mid)return query2(rs,mid+1,r,p,q);
    else return max(query2(ls,l,mid,p,mid),query2(rs,mid+1,r,mid+1,q));
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i];
        build(1,1,n);
        while(m--)
        {
            int op,l,r;
            cin>>op>>l>>r;
            if(op==0)
            {
                int v;
                cin>>v;
                minset(1,1,n,l,r,v);
            }
            else if(op==1)cout<<query2(1,1,n,l,r)<<'\n';
            else cout<<query(1,1,n,l,r)<<'\n';
        }
    }
    return 0;
}