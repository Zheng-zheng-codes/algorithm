//https://www.luogu.com.cn/problem/P2986
//重心的性质：树上的边权如果都为正数，不管边权怎么分布，所有节点走向重心的总距离和最小
//对于带点权的树来说每个节点的大小变成了该节点的点权之和
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
int a[maxn];
vector<pii>tu[maxn];
int siz[maxn];
int sum;
int best;
int reunion;//用来记录重心
int path[maxn];
void dfs(int node,int fa)
{
    int ms=0;
    siz[node]=a[node];
    for(int i=0;i<tu[node].size();++i)
    {
        int tmp=tu[node][i].first;
        if(tmp==fa)continue;
        dfs(tmp,node);
        siz[node]+=siz[tmp];
        ms=max(siz[tmp],ms);
    }
    ms=max(ms,sum-siz[node]);
    if(ms<best)
    {
        reunion=node;
        best=ms;
    }
}
void dfs2(int node,int fa)
{
    path[node]+=path[fa];
    for(int i=0;i<tu[node].size();++i)
    {
        int v=tu[node][i].first;
        if(v==fa)continue;
        int w=tu[node][i].second;
        path[v]+=w;
        dfs2(v,node);
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    best=INT_MAX;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)sum+=a[i];
    for(int i=0;i<n-1;++i)
    {
        int x,y,l;cin>>x>>y>>l;
        tu[x].push_back({y,l});
        tu[y].push_back({x,l});
    }
    dfs(1,0);
    dfs2(reunion,0);
    int ans=0;
    for(int i=1;i<=n;++i)ans+=path[i]*a[i];
    cout<<ans;
}