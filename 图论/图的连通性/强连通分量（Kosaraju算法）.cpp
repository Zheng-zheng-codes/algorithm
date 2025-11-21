//https://www.luogu.com.cn/problem/B3609
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int>tu[maxn];//图
vector<int>rtu[maxn];//反图
vector<int>order;//图的后序序列
bool jud[maxn];
int where[maxn];//每个节点所在的连通分量的序号
vector<vector<int>>scc;//记录每个强连通分量的节点
void init(int n)
{
    order.clear();
    scc.clear();
    for(int i=1;i<=n;i++)
    {
        tu[i].clear();
        rtu[i].clear();
        jud[i]=0;
    }
}
void dfs1(int u)
//第一次dfs:得到原图的后序访问顺序
{
    jud[u]=1;
    for(auto v:tu[u])
    {
        if(!jud[v])dfs1(v);
    }
    order.push_back(u);
}
void dfs2(int u,vector<int>&ans)
//第二次dfs:按照后序访问顺序的结果再进行一次后序dfs
{
    jud[u]=1;
    ans.push_back(u);
    for(int v:rtu[u])
    {
        if(!jud[v])dfs2(v,ans);
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
        rtu[b].push_back(a);
    }
    for(int i=1;i<=n;++i)
    {
        if(!jud[i])dfs1(i);
    }
    for(int i=1;i<=n;++i)jud[i]=0;
    int id=0;
    for(int i=order.size()-1;i>=0;--i)
    {
        int v=order[i];
        if(!jud[v])
        {
            vector<int>ans;
            dfs2(v,ans);
            sort(ans.begin(),ans.end());
            scc.push_back(ans);
            for(int i:ans)where[i]=id;
            id++;
        }
    }
    cout<<id<<'\n';
    vector<bool>jud2(id,0);
    for(int i=1;i<=n;++i)
    {
        int num=where[i];
        if(!jud2[num])
        {
            for(int u:scc[num])cout<<u<<' ';
            cout<<'\n';
            jud2[num]=1;
        }
    }
}