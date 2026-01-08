//https://acm.hdu.edu.cn/showproblem.php?pid=7464
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
void solve()
{
    int n,m,k;cin>>n>>m>>k;
    vector<pii>tu[maxn];
    for(int i=1;i<=m;++i)
    {
        int u,v,t;cin>>u>>v>>t;
        tu[u].push_back({v,t});
        tu[v].push_back({u,t});
    }
    vector<int>dis(n+1,LLONG_MAX);
    vector<bool>jud(n+1,0);
    dis[1]=0;
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    pq.push({0,1});
    while(!pq.empty())
    {
        auto [a,b]=pq.top();//距离 节点
        pq.pop();
        if(jud[b])continue;
        jud[b]=1;
        for(int i=0;i<tu[b].size();++i)
        {
            auto [node,weight]=tu[b][i];
            if(!jud[node]&&dis[node]>=dis[b]+weight)
            {
                dis[node]=min(weight+dis[b],dis[node]);
                pq.push({dis[node],node});
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        dis[i]=min(dis[i],(1|i)*k);
        for(int j=(-i)&i;j;j=(j-1)&i)
        {
            dis[i]=min(dis[i],dis[j]+(j|i)*k);
        }
    }
    for(int i=1;i<=n;++i)
    {
        jud[i]=0;
        pq.push({dis[i],i});
    }
    for(int i=1;i<=n;++i)
    pq.push({0,1});
    while(!pq.empty())
    {
        auto [a,b]=pq.top();//距离 节点
        pq.pop();
        if(jud[b])continue;
        jud[b]=1;
        for(int i=0;i<tu[b].size();++i)
        {
            auto [node,weight]=tu[b][i];
            if(!jud[node]&&dis[node]>=dis[b]+weight)
            {
                dis[node]=min(weight+dis[b],dis[node]);
                pq.push({dis[node],node});
            }
        }
    }
    for(int i=2;i<=n;++i)cout<<dis[i]<<' ';
    cout<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}