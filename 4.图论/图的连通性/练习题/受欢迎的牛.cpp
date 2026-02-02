//https://www.luogu.com.cn/problem/P2341
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int>tu[maxn];
int dfn[maxn];
int low[maxn];
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
        else if(insta[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
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
//把每个强连通分量进行缩点，出度为0的强连通分量如果只有一个那么这里面的牛都是受欢迎的
//否则有0个
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
    int siz=scc.size();
    if(siz==1)
    {
        cout<<n;
        return 0;
    }
    vector<int>outdeg(n,0);
    for(int u=1;u<=n;++u)
    {
        for(auto v:tu[u])
        {
            if(where[u]!=where[v])
            {
                outdeg[where[u]]++;
            }
        }
    }
    int ans=0;
    bool jud=0;
    for(int i=0;i<siz;++i)
    {
        if(outdeg[i]==0)
        {
            if(jud)
            {
                cout<<0;
                return 0;
            }
            ans+=scc[i].size();
            jud=1;
        }
    }
    cout<<ans;
}