#include<bits/stdc++.h>
#define ls t[k].l
#define rs t[k].r
#define int long long
using namespace std;
const int maxn=8e4;
struct tree
{
    int l;
    int r;
    int sum;
    int lz;
    tree(){lz=0;sum=0;l=0;r=0;}
}t[maxn];
int cnt=1;
void pushup(int k)
{
    t[k].sum=t[ls].sum+t[rs].sum;
}
void puttag(int k,int l,int r,int val)
{
    t[k].sum+=val*(r-l+1);
    t[k].lz+=val;
}
void pushdown(int k,int l,int r)
{
    if(t[k].lz)
    {
        int mid=l+r>>1;
        if(!t[k].l)t[k].l=++cnt;
        if(!t[k].r)t[k].r=++cnt;
        puttag(ls,l,mid,t[k].lz);
        puttag(rs,mid+1,r,t[k].lz);
        t[k].lz=0;
    }
}
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)
    {
        if(!t[k].l)t[k].l=++cnt;
        return query(ls,l,mid,p,q);
    }
    else if(p>mid)
    {
        if(!t[k].r)t[k].r=++cnt;
        return query(rs,mid+1,r,p,q);
    }
    else 
    {
        if(!t[k].l)t[k].l=++cnt;
        if(!t[k].r)t[k].r=++cnt;
        return query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q);
    }
}
void modify(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        puttag(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)
    {
        if(!t[k].l)t[k].l=++cnt;
        modify(ls,l,mid,p,q,val);
    }
    else if(p>mid)
    {
        if(!t[k].r)t[k].r=++cnt;
        modify(rs,mid+1,r,p,q,val);
    }
    else 
    {
        if(!t[k].l)t[k].l=++cnt;
        if(!t[k].r)t[k].r=++cnt;
        modify(ls,l,mid,p,mid,val),modify(rs,mid+1,r,mid+1,q,val);
    }
    pushup(k);
}
signed main()
{
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1)
        {
            int num;
            cin>>num;
            modify(1,1,n,x,y,num);
        }
        else cout<<query(1,1,n,x,y)<<'\n';
    }
    return 0;
}
