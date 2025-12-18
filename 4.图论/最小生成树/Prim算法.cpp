#include<bits/stdc++.h>
using namespace std;
const int maxn=5001;
using pii=pair<int,int>;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    vector<pii>tu[maxn];//(权值，到哪里)
    int u,v,w;
    while(m--)
    {
        cin>>u>>v>>w;
        tu[u].push_back({w,v});
        tu[v].push_back({w,u});
    }
    vector<bool>visited(n+1,0);
    priority_queue<pii,vector<pii>,greater<pii>>pq;//数对排序默认用字典序
    visited[1]=1;
    int cnt=1;
    int ans=0;
    for(auto&e:tu[1])
    {
        if(!visited[e.second])pq.push(e);
    }
    while(!pq.empty())
    {
        pii t=pq.top();
        pq.pop();
        if(!visited[t.second])
        {
            ans+=t.first;
            cnt++;
            visited[t.second]=1;
            for(auto&e:tu[t.second])
            {
                if(!visited[e.second])pq.push(e);
            }
        }
    }
    if(cnt==n)cout<<ans<<'\n';
    else cout<<"orz"<<'\n';
    return 0;
}