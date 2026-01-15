//https://acm.hdu.edu.cn/showproblem.php?pid=7463
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int d[maxn];//差分数组
struct tree
{
    bool ifup;
    bool ifdown;
    bool ifsimple;
    bool same;
}t[maxn<<2];
void pushup(int k,int l,int r)
{
    int mid=l+r>>1;
    if(t[ls].ifup&&t[rs].ifup)t[k].ifup=1;
    else t[k].ifup=0;
    if(t[ls].ifdown&&t[rs].ifdown)t[k].ifdown=1;
    else t[k].ifdown=0;
    if(t[ls].ifsimple&&t[rs].ifdown)t[k].ifsimple=1;
    else if(t[ls].ifup&&t[rs].ifsimple)t[k].ifsimple=1;
    else if(t[ls].ifup&&t[rs].ifdown)t[k].ifsimple=1;
    else t[k].ifsimple=0;
    if(t[ls].same&&t[rs].same)t[k].same=1;
    else t[k].same=0;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        if(d[l]>0)
        {
            t[k].ifup=1;
            t[k].same=t[k].ifdown=0;
        }
        else if(d[l]<0)
        {
            t[k].ifdown=1;
            t[k].ifup=t[k].same=0;
        }
        else
        {
            t[k].same=1;
            t[k].ifup=t[k].ifdown=0;
        }
        t[k].ifsimple=0;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k,l,r);
}
void add(int k,int l,int r,int p,int num)
{
    if(l==r)
    {
        d[l]+=num;
        if(d[l]>0)
        {
            t[k].ifup=1;
            t[k].ifdown=t[k].same=0;
        }
        else if(d[l]<0)
        {
            t[k].ifdown=1;
            t[k].ifup=t[k].same=0;
        }
        else 
        {
            t[k].same=1;
            t[k].ifup=t[k].ifdown=0;
        }
        return;
    }
    int mid=l+r>>1;
    if(p<=mid)add(ls,l,mid,p,num);
    else add(rs,mid+1,r,p,num);
    pushup(k,l,r);
}
bool same(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].same;
    int mid=l+r>>1;
    if(mid>=q)return same(ls,l,mid,p,q);
    else if(mid<p)return same(rs,mid+1,r,p,q);
    else 
    {
        bool jud1=same(ls,l,mid,p,mid);
        bool jud2=same(rs,mid+1,r,mid+1,q);
        return jud1&&jud2;
    }
}
bool ifup(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].ifup;
    int mid=l+r>>1;
    if(mid>=q)return ifup(ls,l,mid,p,q);
    else if(mid<p)return ifup(rs,mid+1,r,p,q);
    else 
    {
        bool jud1=ifup(ls,l,mid,p,mid);
        bool jud2=ifup(rs,mid+1,r,mid+1,q);
        return jud1&&jud2;
    }
}
bool ifdown(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].ifdown;
    int mid=l+r>>1;
    if(mid>=q)return ifdown(ls,l,mid,p,q);
    else if(mid<p)return ifdown(rs,mid+1,r,p,q);
    else 
    {
        bool jud1=ifdown(ls,l,mid,p,mid);
        bool jud2=ifdown(rs,mid+1,r,mid+1,q);
        return jud1&&jud2;
    }
}
bool ifsimple(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].ifsimple;
    int mid=l+r>>1;
    if(mid>=q)return ifsimple(ls,l,mid,p,q);
    else if(mid<p)return ifsimple(rs,mid+1,r,p,q);
    else 
    {
        bool juds1=ifsimple(ls,l,mid,p,mid);
        bool juds2=ifsimple(rs,mid+1,r,mid+1,q);
        bool judu1=ifup(ls,l,mid,p,mid);
        bool judd2=ifdown(rs,mid+1,r,mid+1,q);
        if(juds1&&judd2)return 1;
        else if(juds2&&judu1)return 1;
        else if(judu1&&judd2)return 1;
        else return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<n;++i)d[i]=a[i+1]-a[i];
    build(1,1,n-1);
    int q;cin>>q;
    while(q--)
    {
        int op,l,r;cin>>op>>l>>r;
        if(op==1)
        {
            int x;cin>>x;
            add(1,1,n-1,l-1,x);
            add(1,1,n-1,r,-x);
        }
        else if(op==2)
        {
            if(l==r)cout<<1<<'\n';
            else if(same(1,1,n-1,l,r-1))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else if(op==3)
        {
            if(l==r)cout<<1<<'\n';
            else if(ifup(1,1,n-1,l,r-1))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else if(op==4)
        {
            if(l==r)cout<<1<<'\n';
            else if(ifdown(1,1,n-1,l,r-1))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else
        {
            if(ifsimple(1,1,n-1,l,r-1))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
    }
}