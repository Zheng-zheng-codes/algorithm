/*
题目描述
给定一个长度为 n 的序列 a，要求支持如下三个操作：
给定区间 [l,r]，将区间内每个数都修改为 x。
给定区间 [l,r]，将区间内每个数都加上 x。
给定区间 [l,r]，求区间内的最大值。
输入格式
第一行是两个整数，依次表示序列的长度 n 和操作的个数 q。
第二行有 n 个整数，第 i 个整数表示序列中的第 i 个数ai。
接下来 q 行，每行表示一个操作。每行首先有一个整数 op，表示操作的类型。
若 op=1，则接下来有三个整数 l,r,x，表示将区间 [l,r] 内的每个数都修改为 x。
若 op=2，则接下来有三个整数 l,r,x，表示将区间 [l,r] 内的每个数都加上 x。
若 op=3，则接下来有两个整数 l,r，表示查询区间 [l,r] 内的最大值。
输出格式
对于每个 op=3 的操作，输出一行一个整数表示答案。
*/
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e6+10;
struct tree
{
    int maxnum;
    int addlz;
    int changelz;
    bool updatelz;
    tree(){addlz=0;updatelz=0;}
}t[maxn<<2];
int a[maxn];
void pushup(int k)
{
    t[k].maxnum=max(t[ls].maxnum,t[rs].maxnum);
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].maxnum=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
void putadd(int k,int val)
{
    t[k].maxnum+=val;
    t[k].addlz+=val;
}
void putchange(int k,int val)
{
    t[k].addlz=0;
    t[k].maxnum=val;
    t[k].updatelz=1;
    t[k].changelz=val;
}
void pushdown(int k)
{
    if(t[k].updatelz)
    {
        putchange(ls,t[k].changelz);
        putchange(rs,t[k].changelz);
        t[k].updatelz=0;
    }
    if(t[k].addlz)
    {
        putadd(ls,t[k].addlz);
        putadd(rs,t[k].addlz);
        t[k].addlz=0;
    }
}
void modify(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        putchange(k,val);
        return;
    }
    int mid=l+r>>1;
    pushdown(k);
    if(q<=mid)modify(ls,l,mid,p,q,val);
    else if(p>mid)modify(rs,mid+1,r,p,q,val);
    else modify(ls,l,mid,p,mid,val),modify(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
void add(int k,int l,int r,int p,int q,int val)
{
    if(l==p&&r==q)
    {
        putadd(k,val);
        return;
    }
    int mid=l+r>>1;
    pushdown(k);
    if(q<=mid)add(ls,l,mid,p,q,val);
    else if(p>mid)add(rs,mid+1,r,p,q,val);
    else add(ls,l,mid,p,mid,val),add(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
int query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].maxnum;
    int mid=l+r>>1;
    pushdown(k);
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return max(query(ls,l,mid,p,mid),query(rs,mid+1,r,mid+1,q));
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
            int val;
            cin>>val;
            modify(1,1,n,l,r,val);
        }
        else if(op==2)
        {
            int val;
            cin>>val;
            add(1,1,n,l,r,val);
        }
        else cout<<query(1,1,n,l,r)<<'\n';
    }
    return 0;
}
