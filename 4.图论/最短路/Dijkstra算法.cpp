/*
题目描述
给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
数据保证你能从 s 出发到任意点。
输入格式
第一行为三个正整数 n,m,s。 第二行起 m 行，每行三个非负整数 ui,vi,wi，表示从 ui到 vi有一条权值为 w i的有向边。
输出格式
输出一行 n 个空格分隔的非负整数,表示 s到每个点的距离。
*/
//邻接表+优先队列
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    vector<vector<pii>>tu(n+1);
    int u,v,w;
    while(m--)
    {
        cin>>u>>v>>w;
        tu[u].push_back({v,w});
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,s});//{距离，结点}
    vector<int>dis(n+1,INT_MAX);
    vector<bool>visited(n+1,0);
    dis[s]=0;
    while(!pq.empty())
    {
        auto [a,b]=pq.top();
        pq.pop();
        if(visited[b])continue;
        visited[b]=1;
        for(auto &[c,d]:tu[b])
        {
            if(!visited[c]&&dis[c]>dis[b]+d)
            {
                dis[c]=dis[b]+d;
                pq.push({dis[c],c});
            }
        }
    }
    for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
    return 0;
}