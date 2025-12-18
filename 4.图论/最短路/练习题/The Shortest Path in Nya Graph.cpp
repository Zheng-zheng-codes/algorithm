//https://acm.hdu.edu.cn/showproblem.php?pid=4725
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
int node[maxn];
int dis[maxn];
vector<pii>tu[maxn];
bool visited[maxn];
unordered_map<int,vector<int>>um;
bool usedlayer[maxn];
void init(int n)
{
    um.clear();
    for(int i=1;i<=n;++i)
    {
        tu[i].clear();
        visited[i]=0;
        usedlayer[i]=0;
        dis[i]=INT_MAX;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    for(int i=1;i<=t;++i)
    {
        cout<<"Case #"<<i<<": ";
        int n,m,c;cin>>n>>m>>c;
        init(n);
        for(int j=1;j<=n;++j)
        {
            cin>>node[j];
            um[node[j]].push_back(j);
        }
        while(m--)
        {
            int u,v,w;cin>>u>>v>>w;
            tu[u].push_back({v,w});
            tu[v].push_back({u,w});
        }
        priority_queue<pii,vector<pii>,greater<pii>>pq;
        pq.push({0,1});
        dis[1]=0;
        while(!pq.empty())
        {
            auto [a,b]=pq.top();
            pq.pop();
            if(visited[b])continue;
            visited[b]=1;
            for(int j=0;j<tu[b].size();++j)
            {
                auto [e,d]=tu[b][j];//点 距离
                if(!visited[e]&&dis[e]>dis[b]+d)
                {
                    dis[e]=dis[b]+d;
                    pq.push({dis[e],e});
                }
            }
            int layer=node[b];
            if(um.count(layer-1)&&!usedlayer[layer-1])
            {
                usedlayer[layer-1]=1;
                for(int j=0;j<um[layer-1].size();++j)
                {
                    int n=um[layer-1][j];
                    if(!visited[n]&&dis[n]>dis[b]+c)
                    {
                        dis[n]=dis[b]+c;
                        pq.push({dis[n],n});
                    }
                }
            }
            if(um.count(layer+1)&&!usedlayer[layer+1])
            {
                usedlayer[layer+1]=1;
                for(int j=0;j<um[layer+1].size();++j)
                {
                    int n=um[layer+1][j];
                    if(!visited[n]&&dis[n]>dis[b]+c)
                    {
                        dis[n]=dis[b]+c;
                        pq.push({dis[n],n});
                    }
                }
            }
        }
        if(dis[n]==INT_MAX)cout<<-1<<'\n';
        else cout<<dis[n]<<'\n';
    }
}