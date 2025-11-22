//https://www.luogu.com.cn/problem/P8435
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
vector<int>tu[maxn];
int dfn[maxn];
int low[maxn];
int cnt;
vector<vector<int>>dcc;
stack<int>st;
void init(int n)
{
    while(!st.empty())st.pop();
    dcc.clear();
    for(int i=1;i<=n;++i)
    {
        dfn[i]=0;
        low[i]=0;
        tu[i].clear();
    }
    cnt=0;
}
void dfs(int u,int fa)
{
    dfn[u]=low[u]=++cnt;
    int son=0;
    st.push(u);
    for(int v:tu[u])
    {
        if(!dfn[v])
        {
            son++;
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])
            {
                vector<int>ans;
                while(1)
                {
                    int tmp=st.top();
                    st.pop();
                    ans.push_back(tmp);
                    if(tmp==v)break;
                }
                ans.push_back(u);
                dcc.push_back(ans);
            }
        }
        else if(v!=fa)low[u]=min(low[u],dfn[v]);
    }
    if(fa==-1&&son==0)
    {
        dcc.push_back({u});
        st.pop();
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
        int u,v;cin>>u>>v;
        tu[u].push_back(v);
        tu[v].push_back(u);
    }
    for(int i=1;i<=n;++i)
    {
        if(!dfn[i])dfs(i,-1);
    }
    cout<<dcc.size()<<'\n';
    for(int i=0;i<dcc.size();++i)
    {
        cout<<dcc[i].size()<<' ';
        for(int j=0;j<dcc[i].size();++j)
        {
            cout<<dcc[i][j]<<' ';
        }
        cout<<'\n';
    }
}