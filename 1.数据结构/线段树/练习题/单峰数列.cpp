//
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
int a[maxn];
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
    if(t[ls].ifup&&t[rs].ifup&&a[mid]<a[mid+1])t[k].ifup=1;
    else t[k].ifup=0;
    if(t[ls].ifdown&&t[rs].ifdown&&a[mid]>a[mid+1])t[k].ifdown=1;
    else t[k].ifdown=0;
    if(r-l+1<3)t[k].ifsimple=0;
    else if(r-l==2)t[k].ifsimple=a[mid]>a[mid+1]&&a[mid]>a[mid-1];
    else if(t[ls].ifsimple&&t[rs].ifdown&&a[mid]>a[mid+1])t[k].ifsimple=1;
    else if(t[ls].ifup&&t[rs].ifsimple&&a[mid]<a[mid+1])t[k].ifsimple=1;
    else if(t[ls].ifup&&t[rs].ifdown)t[k].ifsimple=1;
    else t[k].ifsimple=0;
    if(t[ls].same&&t[rs].same&&a[mid]==a[mid+1])t[k].same=1;
    else t[k].same=0;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].ifup=t[k].ifdown=1;
        t[k].ifsimple=0;
        t[k].same=1;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k,l,r);
}
void add(int k,int l,int r,int p,int q,int num)
{
    if(l==r)
    {
        a[l]+=num;
        t[k].ifup=t[k].ifdown=1;
        t[k].ifsimple=0;
        t[k].same=1;
        return;
    }
    int mid=l+r>>1;
    if(mid>=q)add(ls,l,mid,p,q,num);
    else if(mid<p)add(rs,mid+1,r,p,q,num);
    else add(ls,l,mid,p,mid,num),add(rs,mid+1,r,mid+1,q,num);
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
        bool jud3=a[mid]==a[mid+1];
        return jud1&&jud2&&jud3;
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
        bool jud3=a[mid]<a[mid+1];
        return jud1&&jud2&&jud3;
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
        bool jud3=a[mid]>a[mid+1];
        return jud1&&jud2&&jud3;
    }
}
bool ifsimple(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].ifsimple;
    if(q-p+1<3)return 0;
    if(q-p+1==3)
    {
        int m=p+q>>1;
        return a[m]>a[p]&&a[m]>a[q];
    }
    int mid=l+r>>1;
    if(mid>=q)return ifsimple(ls,l,mid,p,q);
    else if(mid<p)return ifsimple(rs,mid+1,r,p,q);
    else 
    {
        bool juds1=ifsimple(ls,l,mid,p,mid);
        bool juds2=ifsimple(rs,mid+1,r,mid+1,q);
        bool judu1=ifup(ls,l,mid,p,mid);
        bool judu2=ifup(rs,mid+1,r,mid+1,q);
        bool judd1=ifdown(ls,l,mid,p,mid);
        bool judd2=ifdown(rs,mid+1,r,mid+1,q);
        if(juds1&&judd2&&a[mid]>a[mid+1])return 1;
        else if(juds2&&judu1&&a[mid]<a[mid+1])return 1;
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
    build(1,1,n);
    int q;cin>>q;
    while(q--)
    {
        int op,l,r;cin>>op>>l>>r;
        if(op==1)
        {
            int x;cin>>x;
            add(1,1,n,l,r,x);
        }
        else if(op==2)
        {
            if(same(1,1,n,l,r))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else if(op==3)
        {
            if(ifup(1,1,n,l,r))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else if(op==4)
        {
            if(ifdown(1,1,n,l,r))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
        else
        {
            if(ifsimple(1,1,n,l,r))cout<<1<<'\n';
            else cout<<0<<'\n';
        }
    }
}