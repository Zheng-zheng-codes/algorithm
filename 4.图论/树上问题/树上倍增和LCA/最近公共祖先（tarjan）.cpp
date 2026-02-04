//https://www.luogu.com.cn/problem/P3379
//tarjan算法找最近公共祖先：离线查询
//从根节点开始遍历整棵树：
//遍历完一个节点的所有子树后把子树的所有节点加在父节点的集合后面
//当遍历完一个节点的所有子树后，查询和这个节点相关的所有查询，如果另一个节点已经遍历过了，返回另一个节点当前集合的头，否则跳过
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=5e5+10;
vector<int>tu[maxn];
int fa[maxn];
bool jud[maxn];
vector<pii>querys[maxn];
int ans[maxn];
void init(int n)
{
    for(int i=1;i<=n;++i)fa[i]=i;
}
int find(int a)
{
    if(a!=fa[a])fa[a]=find(fa[a]);
    return fa[a];
}
void tarjan(int s)
{
    jud[s]=1;
    for(int i=0;i<tu[s].size();++i)
    {
        if(jud[tu[s][i]])continue;
        tarjan(tu[s][i]);
        fa[tu[s][i]]=s;
    }
    for(int i=0;i<querys[s].size();++i)
    {
        pii tmp=querys[s][i];
        if(!jud[tmp.first])continue;
        ans[tmp.second]=find(tmp.first);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,s;cin>>n>>m>>s;
    init(n);
    for(int i=0;i<n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    for(int i=1;i<=m;++i)
    {
        int a,b;cin>>a>>b;
        querys[a].push_back({b,i});
        querys[b].push_back({a,i});
    }
    tarjan(s);
    for(int i=1;i<=m;++i)cout<<ans[i]<<'\n';
}
