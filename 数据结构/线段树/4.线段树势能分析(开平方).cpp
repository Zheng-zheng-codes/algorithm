/*
输入格式
第一行一个整数 n，代表数列中数的个数。
第二行 n 个正整数，表示初始状态下数列中的数。
第三行一个整数 m，表示有 m 次操作。
接下来 m 行每行三个整数 k l r。
k=0 表示给 [l,r] 中的每个数开平方（下取整）。
k=1 表示询问 [l,r] 中各个数的和。
数据中有可能 l>r，所以遇到这种情况请交换 l 和 r。
输出格式
对于询问操作，每行输出一个回答。
*/
//不需要也不能懒标记-->10^12开方6次就变成1了（可以剪枝）
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
void modify(int k,int l,int r,int p,int q)
{
    if(p>r||q<l)return;
    if(t[k].maxn<=1)return;
    if(l==r)
    {
        t[k].maxn=(long long)sqrt(t[k].maxn);
        t[k].sum=(long long)sqrt(t[k].sum);
        return;
    }
    int mid=l+r>>1;
    if(q<=mid)modify(ls,l,mid,p,q);
    else if(p>mid)modify(rs,mid+1,r,p,q);
    else modify(ls,l,mid,p,mid),modify(rs,mid+1,r,mid+1,q);
    pushup(k);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    int m;
    cin>>m;
    while(m--)
    {
        int k,l,r;
        cin>>k>>l>>r;
        if(l>r)swap(l,r);
        if(k==0)modify(1,1,n,l,r);
        else cout<<query(1,1,n,l,r)<<'\n';
    }
    return 0;
}