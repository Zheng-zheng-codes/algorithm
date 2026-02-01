//https://www.luogu.com.cn/problem/P1972
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int a[maxn];
struct que
{
    int l,r,idx;
}q[maxn];
int n;
int tree[maxn];
unordered_map<int,int>um;
int ans[maxn];
static bool cmp(que a,que b)
{
    return a.r<b.r;
}
void add(int pos,int num)
{
    while(pos<=n)
    {
        tree[pos]+=num;
        pos+=pos&(-pos);
    }
}
int query(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    int m;cin>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>q[i].l>>q[i].r;
        q[i].idx=i;
    }
    sort(q+1,q+1+m,cmp);
    int s=1;
    for(int i=1;i<=m;++i)
    {
        while(s<=q[i].r)
        {
            if(!um.count(a[s]))
            {
                um[a[s]]=s;
                add(s,1);
            }
            else
            {
                add(um[a[s]],-1);
                add(s,1);
                um[a[s]]=s;
            }
            ++s;
        }
        ans[q[i].idx]=query(q[i].r)-query(q[i].l-1);
    }
    for(int i=1;i<=m;++i)cout<<ans[i]<<'\n';
}