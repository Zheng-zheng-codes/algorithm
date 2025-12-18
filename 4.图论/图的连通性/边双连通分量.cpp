//https://www.luogu.com.cn/problem/P8436
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=5e5+10;
const int maxm=4e6+10;
vector<pii>g[maxn];
int U[maxm],V[maxm];
int dfn[maxn],low[maxn],cnt;
bool isbridge[maxm];
int id[maxn];
vector<vector<int>>ans;
void dfs_bridge(int u,int fa)
{
    dfn[u]=low[u]=++cnt;
    for(auto [v,idx]:g[u])
    {
        if(!dfn[v])
        {
            dfs_bridge(v,idx);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u])isbridge[idx]=1;
            //这里没有等号（防止重边）-->注意和割点的区别
        }
        else
        {
            if(idx==fa)continue;
            low[u]=min(low[u],dfn[v]);
        }
    }
}
void dfs_chunk(int u,int num)
{
    id[u]=num;
    ans[num].push_back(u);
    for(auto[v,idx]:g[u])
    {
        if(!id[v]&&!isbridge[idx])dfs_chunk(v,num);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        int a,b;cin>>a>>b;
        g[a].push_back({b,i});
        g[b].push_back({a,i});
        U[i]=a;
        V[i]=b;
    }
    for(int i=1;i<=n;++i)
    {
        if(!dfn[i])dfs_bridge(i,-1);
    }
    ans.resize(n+1);
    int num=0;
    for(int i=1;i<=n;++i)
    {
        if(!id[i])dfs_chunk(i,++num);
    }
    cout<<num<<'\n';
    for(int i=1;i<=num;++i)
    {
        cout<<ans[i].size()<<' ';
        for(int j=0;j<ans[i].size();j++)cout<<ans[i][j]<<' ';
    }
}