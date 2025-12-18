//https://www.luogu.com.cn/problem/P3119
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
    //将得到的强连通分量缩点，并分别建立图和反图
    int siz=scc.size();
    vector<unordered_set<int>>tmp(siz);
    vector<vector<int>>g(siz),rg(siz);
    vector<int>indeg(siz),rindeg(siz);
    for(int u=1;u<=n;++u)
    {
        for(auto v:tu[u])
        {
            int cu=where[u],cv=where[v];
            if(cu!=cv&&!tmp[cu].count(cv))
            {
                tmp[cu].insert(cv);
                g[cu].push_back(cv);
                rg[cv].push_back(cu);
            }
        }
    }
    int s=where[1];
    vector<bool>jud1(siz,0);//用来判断从起点所在的强连通分量能不能到达
    queue<int>q;
    jud1[s]=1;
    q.push(s);//用bfs判断能不能走到
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(auto v:g[u])
        {
            if(!jud1[v]) 
            {
                jud1[v]=1;
                q.push(v);
            }
        }
    }
    for(int u=0;u<siz;++u)//得到入度进行拓扑排序
    {
        if(!jud1[u])continue;
        for(int v:g[u])if(jud1[u])indeg[v]++;
    }
    vector<int>topo1;
    queue<int>q1;
    for(int i=0;i<siz;++i)
    {
        if(indeg[i]==0&&jud1[i])q1.push(i); 
    }
    vector<int>dp1(siz,0);
    dp1[s]=scc[s].size();
    while(!q1.empty())
    {
        int u=q1.front();
        q1.pop();
        topo1.push_back(u);
        for(int v:g[u])
        {
            if(jud1[v]&&--indeg[v]==0)
            {
                q1.push(v);
            }
        }
    }
    //按照拓扑排序之后的顺序进行对dp1的更新
    //dp1[i]:图中从起点到i的最长路程
    for(int i=0;i<topo1.size();++i)
    {
        int u=topo1[i];
        if(dp1[u]==0)continue;
        for(auto v:g[u])
        {
            if(jud1[v])
            {
                int temp=dp1[u]+scc[v].size();
                dp1[v]=max(dp1[v],temp);
            }
        }
    }
    vector<bool>jud2(siz,0);//用来判断反图中起点能不能到达这里也就是原图中能不能走回起点
    jud2[s]=1;
    q.push(s);
    while(!q.empty())//用bfs判断
    {
        int u=q.front();
        q.pop();
        for(auto v:rg[u])
        {
            if(!jud2[v])
            {
                jud2[v]=1;
                q.push(v);
            }
        }
    }
    for(int u=0;u<siz;++u)//给反图拓扑排序
    {
        if(!jud2[u])continue;
        for(int v:rg[u])if(jud2[u])rindeg[v]++;
    }
    vector<int>topo2;
    queue<int>q2;
    for(int i=0;i<siz;++i)
    {
        if(rindeg[i]==0&&jud2[i])q2.push(i); 
    }
    vector<int>dp2(siz,0);
    dp2[s]=scc[s].size();
    while(!q2.empty())
    {
        int u=q2.front();
        q2.pop();
        topo2.push_back(u);
        for(int v:rg[u])
        {
            if(jud2[v]&&--rindeg[v]==0)
            {
                q2.push(v);
            }
        }
    }
    //dp2[i]；反图中起点到i的最长距离（原图中回到起点的最长距离）
    for(int i=0;i<topo2.size();++i)
    {
        int u=topo2[i];
        if(dp2[u]==0)continue;
        for(auto v:rg[u])
        {
            if(jud2[v])
            {
                int temp=dp2[u]+scc[v].size();
                dp2[v]=max(dp2[v],temp);
            }
        }
    }
    int ans=scc[s].size();//在起点的强连通分量中徘徊
    for(int i=0;i<siz;++i)
    {
        for(int j:g[i])//考虑一条边反过来
        {
            if(dp1[j]>0&&dp2[i]>0)
            {
                int temp=dp1[j]+dp2[i]-scc[s].size();
                ans=max(ans,temp);
            }
        }
    }
    cout<<ans<<'\n';
}