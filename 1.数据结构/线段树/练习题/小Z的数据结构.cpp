/*
题目描述
给定一长度为n的[0,1,2,...,n]排列a，以及q个操作，操作包括以下三种类型：
给定l,r，交换al,ar
给定k，询问当前a中长度为k的连续子序列的MEX最大为多少
输入描述
第一行包含两个整数n,q，分别表示排列长度和操作次数
第二行包含n个用空格分隔的整数，表示序列a，保证序列a一定是以0起始的排列
接下来q行每行包含若干个整数，表示一个操作，具体如下：
操作1：格式1 l r含义：交换序列中al,a r
操作2：格式2 k含义：查询当前a中长度为k的子数组的MEX最大为多少
输出描述
输出包含若干行整数，即为所有操作2的结果。
*/
//MEX：一串数中最小的没出现的自然数
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
struct tree
{
    int minn;
    int maxn;
}t[maxn<<2];//表示区间内的数所在的最小和最大位置
int a[maxn];
int pos[maxn];//用来记录排列里的每个数所在的位置
void pushup(int k,int l,int r)
{
    t[k].maxn=max(t[ls].maxn,t[rs].maxn);
    t[k].minn=min(t[ls].minn,t[rs].minn);
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].minn=pos[l];
        t[k].maxn=pos[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k,l,r);
}
void modify(int k,int l,int r,int pos,int num)
{
    if(l==r)
    {
        t[k].minn=t[k].maxn=num;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid)modify(ls,l,mid,pos,num);
    else modify(rs,mid+1,r,pos,num);
    pushup(k,l,r);
}
pii query(int k,int l,int r,int p,int q)//查询p到q这个区间内的最大最小位置
{
    if(l==p&&r==q)return {t[k].minn,t[k].maxn};
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else
    {
        pii p1=query(ls,l,mid,p,mid);
        pii p2=query(rs,mid+1,r,mid+1,q);
        pii ans;
        ans.first=min(p1.first,p2.first);
        ans.second=max(p1.second,p2.second);
        return ans;
    }
}
bool check(int x,int k,int n)//检查0~x这个区间的长度是否不大于k
{
    pii tmp=query(1,0,n-1,0,x);
    return tmp.second-tmp.first+1<=k;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        pos[a[i]]=i;
    }
    build(1,0,n-1);
    while(q--)
    {
        int op;cin>>op;
        if(op==1)//单点修改
        {
            int l,r;cin>>l>>r;
            modify(1,0,n-1,a[l],r);
            modify(1,0,n-1,a[r],l);
            swap(pos[a[l]],pos[a[r]]);
            swap(a[l],a[r]);
        }
        else
        {
            int k;cin>>k;
            int l=0,r=n-1,ans=-1;
            while(l<=r)
            {
                int mid=l+r>>1;
                if(check(mid,k,n))
                {
                    ans=mid;
                    l=mid+1;
                }
                else r=mid-1;
            }
            cout<<ans+1<<'\n';
        }
    }
}