//https://www.luogu.com.cn/problem/B3609
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int>tu[maxn];
int dfn[maxn];//访问的次序
int low[maxn];//记录当前节点所有和它联通的点的dfn最小值
int cnt;
bool insta[maxn];
stack<int>sta;
int where[maxn];
int id;
bool jud[maxn];
vector<vector<int>>scc;
void init(int n)
{
    cnt=0;
    id=0;
    scc.clear();
    for(int i=1;i<=n;++i)
    {
        tu[i].clear();
        dfn[i]=low[i]=where[i]=jud[i]=0;
        insta[i]=0;
    }
    while(!sta.empty())sta.pop();
}
void dfs(int u)
{
    low[u]=dfn[u]=++cnt;
    sta.push(u);
    insta[u]=1;
    for(int i=0;i<tu[u].size();++i)
    {
        int v=tu[u][i];
        if(!dfn[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(insta[v])low[u]=min(low[u],dfn[v]);//栈里面的才有回边
    }
    if(dfn[u]==low[u])//不能再往前走了-->强连通分量
    //dfn[u]>low[u]:父树是强连通分量的根-->还需要回溯
    {
        vector<int>ans;
        while(1)
        {
            int x=sta.top();
            sta.pop();
            ans.push_back(x);
            insta[x]=0;
            if(x==u)break;
        }
        sort(ans.begin(),ans.end());
        for(int i=0;i<ans.size();++i)where[ans[i]]=id;
        id++;
        scc.push_back(ans);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    init(n);
    while(m--)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
    }
    for(int i=1;i<=n;++i)
    {
        if(!dfn[i])dfs(i);
    }
    cout<<scc.size()<<'\n';
    for(int i=1;i<=n;++i)
    {
        if(jud[i])continue;
        int idx=where[i];
        for(int j=0;j<scc[idx].size();++j)
        {
            cout<<scc[idx][j]<<' ';
            jud[scc[idx][j]]=1;
        }
        cout<<'\n';
    }
}