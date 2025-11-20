/*
题目描述
给定一个 n 个点的有向图，请求出图中是否存在从顶点 1 出发能到达的负环。
负环的定义是：一条边权之和为负数的回路。
输入格式
本题单测试点有多组测试数据。
输入的第一行是一个整数 T，表示测试数据的组数。对于每组数据的格式如下：
第一行有两个整数，分别表示图的点数 n 和接下来给出边信息的条数 m。
接下来 m 行，每行三个整数 u,v,w。
若 w≥0，则表示存在一条从 u 至 v 边权为 w 的边，还存在一条从 v 至 u 边权为 w 的边。
若 w<0，则只表示存在一条从 u 至 v 边权为 w 的边。
输出格式
对于每组数据，输出一行一个字符串，若所求负环存在，则输出 YES，否则输出 NO。
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=2001;
const int maxm=6001*2;
int head[maxn],nxt[maxm],to[maxm],wei[maxm],cnt;//链式前向星
int dis[maxn],num[maxn];
bool enter[maxn];//SPFA
//dis为距离
//num用来记录点被松弛了多少次
//enter用来记录点在不在队列中
void build(int n)
{
    cnt=1;
    memset(enter,0,sizeof(bool)*(n+2));
    memset(num,0,sizeof(int)*(n+2));
    memset(head,0,sizeof(int)*(n+2));
    for(int i=1;i<=n;i++)dis[i]=INT_MAX;
}
void add(int u,int v,int w)
{
    to[cnt]=v;
    wei[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt++;
}
bool SPFA(int n)
{
    queue<int>q;
    dis[1]=0;
    num[1]=1;
    enter[1]=1;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        enter[u]=0;
        for(int ei=head[u];ei!=0;ei=nxt[ei])
        {
            int v=to[ei];
            int w=wei[ei];
            if(dis[u]!=INT_MAX&&dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                if(!enter[v])
                {
                    if(++num[v]>n-1)return 1;
                    q.push(v);
                    enter[v]=1;
                }
            }
        }
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        build(n);
        while(m--)
        {
            int u,v,w;
            cin>>u>>v>>w;
            if(w>=0)
            {
                add(u,v,w);
                add(v,u,w);
            }
            else add(u,v,w);
        }
        if(SPFA(n))cout<<"YES"<<"\n";
        else cout<<"NO"<<'\n';
    }
    return 0;
}