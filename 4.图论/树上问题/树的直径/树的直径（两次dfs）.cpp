//https://www.luogu.com.cn/problem/U81904
//无法全部通过，测试用例中有负边
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=5e5+10;
vector<pii>tu[maxn];
int dis[maxn];
int mnode;
int ms;
void dfs(int node,int fa)
{
    for(int i=0;i<tu[node].size();++i)
    {
        pii tmp=tu[node][i];
        if(tmp.first==fa)continue;
        dis[tmp.first]=dis[node]+tmp.second;
        dfs(tmp.first,node);
        if(dis[tmp.first]>ms)
        {
            ms=dis[tmp.first];
            mnode=tmp.first;
        }
    }
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
    dfs(1,0);
    int tmp=mnode;
    mnode=0;
    ms=0;
    for(int i=1;i<=n;++i)dis[i]=0;
    dfs(tmp,0);
    cout<<ms;
}