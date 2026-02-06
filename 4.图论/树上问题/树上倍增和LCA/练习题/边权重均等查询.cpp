//https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/description/
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=10010;
vector<pii>tu[maxn];
int deep[maxn];
int cnt[maxn][27];
int st[maxn][14];
bool jud[maxn];
void dfs(int n)
{
    jud[n]=1;
    for(int i=0;i<tu[n].size();++i)
    {
        int v=tu[n][i].first,w=tu[n][i].second;
        if(jud[v])continue;
        deep[v]=deep[n]+1;
        for(int i=1;i<=26;++i)cnt[v][i]=cnt[n][i];
        cnt[v][w]++;
        st[v][0]=n;
        dfs(v);
    }
}
int lca(int a,int b)
{
    if(deep[a]<deep[b])swap(a,b);
    int tmp=deep[a]-deep[b];
    if(tmp!=0)
    {
        int power=(int)log2(tmp);
        for(int p=power;p>=0;--p)
        {
            if(tmp>=(1<<p))
            {
                tmp-=(1<<p);
                a=st[a][p];
            }
        }
    }
    if(a==b)return a;
    int power=(int)log2(deep[a]);
    for(int p=power;p>=0;--p)
    {
        if(st[a][p]!=st[b][p]&&st[a][p]!=-1)
        {
            a=st[a][p];
            b=st[b][p];
        }
    }
    return st[a][0];
}
vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) 
{
    memset(st,-1,sizeof(st));
    for(int i=0;i<edges.size();++i)
    {
        int u=edges[i][0],v=edges[i][1],w=edges[i][2];
        tu[u].push_back({v,w});
        tu[v].push_back({u,w});
    }
    deep[0]=1;
    dfs(0);
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=0;i<n;++i)
        {
            if(st[i][p-1]!=-1)st[i][p]=st[st[i][p-1]][p-1];
        }
    }
    vector<int>ans;
    for(int i=0;i<queries.size();++i)
    {
        int a=queries[i][0],b=queries[i][1];
        int fa=lca(a,b);
        int num=deep[a]+deep[b]-2*deep[fa];
        int res=0;
        for(int i=1;i<=26;++i)
        {
            int tmp=cnt[a][i]+cnt[b][i]-2*cnt[fa][i];
            res=max(res,tmp);
        }
        ans.push_back(num-res);
    }
    return ans;
}
