/*
题目描述
有一个长度为 n 的数列 {an} 和 m 次操作，操作内容如下：
格式为 1 l r，表示求 i=l∑rai的值并输出。（从l到r求和）
格式为 2 l r x，表示对区间 [l,r] 内每个数取模，模数为 x。
格式为 3 k x，表示将 ak修改为 x。
1≤n,m≤10^5，1≤l,r,k≤n，1≤x≤10^9。
输入格式
第一行两个正整数 n,m，分别表示数列长度和操作次数。
第二行给出长为 n 的数列 {a n}。
接下来 m 行，每行表示一次操作。
输出格式
对于每个操作 1，输出答案，每行一个整数。答案可能大于 2^31−1。
*/
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
struct tree
{
    int sum;
    int maxn;
}t[maxn<<2];
int a[maxn];
void pushup(int k)
{
    t[k].maxn=max(t[ls].maxn,t[rs].maxn);
    t[k].sum=t[ls].sum+t[rs].sum;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].sum=a[l];
        t[k].maxn=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum;
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q);
}
void mod(int k,int l,int r,int p,int q,int x)
{
    if(p>r||q<l)return;
    if(t[k].maxn<x)return;
    if(l==r)
    {
        t[k].maxn%=x;
        t[k].sum%=x;
        return;
    }
    int mid=l+r>>1;
    if(q<=mid)mod(ls,l,mid,p,q,x);
    else if(p>mid)mod(rs,mid+1,r,p,q,x);
    else mod(ls,l,mid,p,mid,x),mod(rs,mid+1,r,mid+1,q,x);
    pushup(k);
}
void modify(int k,int l,int r,int i,int val)
{
    if(l==r)
    {
        t[k].maxn=val;
        t[k].sum=val;   
        return;    
    }
    int mid=l+r>>1;
    if(i<=mid)modify(ls,l,mid,i,val);
    else modify(rs,mid+1,r,i,val);
    pushup(k);
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
        int k,l,r;
        cin>>k>>l>>r;
        if(k==1)cout<<query(1,1,n,l,r)<<'\n';
        else if(k==2)
        {
            int x;
            cin>>x;
            mod(1,1,n,l,r,x);
        }
        else modify(1,1,n,l,r);
    }
    return 0;
}