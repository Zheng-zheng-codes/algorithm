//https://www.luogu.com.cn/problem/U81904
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=5e5+10;
vector<pii>tu[maxn];
int dis[maxn];
int ans[maxn];
int res;
void dp(int node,int fa)
{
    for(int i=0;i<tu[node].size();++i)
    {
        pii tmp=tu[node][i];
        if(tmp.first==fa)continue;
        dp(tmp.first,node);
        int length=dis[tmp.first]+tmp.second;
        ans[node]=max(ans[node],dis[node]+length);
        dis[node]=max(dis[node],length);
    }
    res=max(res,ans[node]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int x,y,w;cin>>x>>y>>w;
        tu[x].push_back({y,w});
        tu[y].push_back({x,w});
    }
    dp(1,0);
    cout<<res;
}