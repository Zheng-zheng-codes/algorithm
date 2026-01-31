/*
题目描述
给定一个长度为 n 的数组，第 i 项为 ai.
你需要支持以下操作:
1. 给定 L,R,X，将区间 [L,R] 中所有元素乘 X.
2. 给定 L,R，查询区间 [L,R] 中所有元素之积的欧拉函数值，因为结果可能很大，你只需要输出答案对10^9+7 取模的结果。
你共需进行q次操作。
输入描述
第一行两个整数 n,q，分别代表数组的长度与操作的次数。
第二行 n 个整数，代表数组内初始元素。
接下来 q 行形式为 1 l r x 或 2 l r ，含义如上所述。
输出描述
输出 q 行，每行一个整数表示对应询问的答案。
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
using ll=long long;
const int maxn=1e6+10;
const int mod=1e9+7;
vector<int>primes;
int inv[305];
int minp[305];
void Euler(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(!minp[i])
        {
            minp[i]=i;
            primes.push_back(i);
        }
        for(int p:primes)
        {
            if(p>minp[i]||i*p>n)break;
            minp[i*p]=p;
        }
    }    
}
ll qpow(int m,int n)
{
    if(n==0)return 1;
    ll tmp=qpow(m,n>>1);
    tmp=tmp*tmp%mod;
    if(n&1)return tmp*m%mod;
    else return tmp;
}
struct tree
{
    ll num;
    ll prime;
    ll lz;
    ll lz2;
    tree(){lz=1;lz2=0;}
}t[maxn<<2];
int a[maxn];
void pushup(int k,int l,int r)
{
    t[k].num=t[ls].num*t[rs].num%mod;
    t[k].prime=t[ls].prime|t[rs].prime;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].num=a[l];
        ll tmp=0;
        for(int i=0;i<primes.size();++i)
        {
           if(a[l]%primes[i]==0)tmp|=(1LL<<i);
        }
        t[k].prime=tmp;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k,l,r);
}
void puttag(int k,int l,int r,ll m)
{
    t[k].num*=qpow(m,r-l+1);
    t[k].num%=mod;
    t[k].lz*=m;
    t[k].lz%=mod;
}
void puttag2(int k,int l,int r,ll m)
{
    t[k].prime|=m;
    t[k].lz2|=m;
}
void pushdown(int k,int l,int r)
{
    if(t[k].lz!=1)
    {
        int mid=l+r>>1;
        puttag(ls,l,mid,t[k].lz);
        puttag(rs,mid+1,r,t[k].lz);
        t[k].lz=1;
    }
    if(t[k].lz2)
    {
        int mid=l+r>>1;
        puttag2(ls,l,mid,t[k].lz2);
        puttag2(rs,mid+1,r,t[k].lz2);
        t[k].lz2=0;
    }
}
void modify(int k,int l,int r,int p,int q,ll m)
{
    if(l==p&&r==q)
    {
        puttag(k,l,r,m);
        return;               
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify(ls,l,mid,p,q,m);
    else if(p>mid)modify(rs,mid+1,r,p,q,m);
    else modify(ls,l,mid,p,mid,m),modify(rs,mid+1,r,mid+1,q,m);
    pushup(k,l,r);
}
void modify2(int k,int l,int r,int p,int q,ll m)
{
    if(l==p&&r==q)
    {
        puttag2(k,l,r,m);
        return;               
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify2(ls,l,mid,p,q,m);
    else if(p>mid)modify2(rs,mid+1,r,p,q,m);
    else modify2(ls,l,mid,p,mid,m),modify2(rs,mid+1,r,mid+1,q,m);
    pushup(k,l,r);
}
ll query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].num;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return query(ls,l,mid,p,mid)*query(rs,mid+1,r,mid+1,q)%mod;
}
ll query2(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].prime;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query2(ls,l,mid,p,q);
    else if(p>mid)return query2(rs,mid+1,r,p,q);
    else return query2(ls,l,mid,p,mid)|query2(rs,mid+1,r,mid+1,q);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    Euler(300);
    for(int i=0;i<primes.size();++i)
    {
        inv[i]=qpow(primes[i],mod-2);
    }
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;++i)cin>>a[i];
    build(1,1,n);
    while(q--)
    {
        int op,l,r;cin>>op>>l>>r;
        if(op==1)
        {
            ll m;cin>>m;
            ll tmp=0;
            for(int i=0;i<primes.size();++i)
            {
                if(m%primes[i]==0)tmp|=(1LL<<i);
            }
            modify(1,1,n,l,r,m);
            modify2(1,1,n,l,r,tmp);
        }
        else
        {
            ll tmp=query(1,1,n,l,r);
            ll tmp2=query2(1,1,n,l,r);
            int i=0;
            while(tmp2&&i<primes.size())
            {
                if(tmp2&1)tmp=(tmp*(primes[i]-1)%mod*inv[i])%mod;
                tmp2>>=1;
                ++i;
            }
            cout<<tmp<<'\n';
        }
    }
}