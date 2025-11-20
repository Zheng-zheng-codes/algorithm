/*
题目描述
如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出 orz。
输入格式
第一行包含两个整数 N,M，表示该图共有 N 个结点和 M 条无向边。
接下来 M 行每行包含三个整数 Xi,Yi,Zi，表示有一条长度为Zi的无向边连接结点 Xi,Yi。
输出格式
如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。如果该图不连通则输出 orz。
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=5001;//最大节点数
const int maxm=200001;//最大边数
struct Edge
{
    int u,v,w;
};
int fa[maxn];
Edge edge[maxm];
static bool cmp(Edge e1,Edge e2)
{
    return e1.w<e2.w;
}
void build(int n)
{
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
    }
}
int find(int x)
{
    if(x!=fa[x])
    {
        fa[x]=find(fa[x]);
    }
    return fa[x];
}
bool unin(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy)
    {
        fa[fx]=fy;
        return 1;
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    build(n);
    for(int i=0;i<m;i++)
    {
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    sort(edge,edge+m,cmp);
    int ans=0;
    int cnt=0;
    for(int i=0;i<m;i++)
    {
        if(unin(edge[i].u,edge[i].v))
        {
            cnt++;
            ans+=edge[i].w;
        }
    }
    if(cnt==n-1)cout<<ans<<'\n';
    else cout<<"orz"<<'\n';
    return 0;
}