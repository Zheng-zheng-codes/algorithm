/*
题目描述
给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
数据保证你能从 s 出发到任意点。
输入格式
第一行为三个正整数 n,m,s。 第二行起 m 行，每行三个非负整数 ui,vi,wi，表示从 ui到 vi有一条权值为 w i的有向边。
输出格式
输出一行 n 个空格分隔的非负整数,表示 s到每个点的距离。
*/
//链式前向星+反向索引堆（这里的堆不能用优先队列实现）
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;//最大节点数
const int maxm=200001;//最大边数
int head[maxn],nxt[maxm],to[maxm],wei[maxm],cnt;//链式前向星
//head[i]:结点i的第一条边的边号
//nxt[i]:边i的下一条边（属于同一个头的下一个边）
//to[i]：边i的终点
//w[i]:边i的权重
//cnt:边数
int heap[maxn],where[maxn],heapsize,dis[maxn];//反向索引堆
//heap[i]:位置i的结点是heap[i]
//where[i]：
//where[i]=-1(点i还没进入堆)
//where[i]=-2(点i已经弹出堆)
//where[i]:点i所在的位置
//heapsize:堆的大小
//dis[i]:到每个结点的距离
void init(int n)
{
    cnt = 1;
    heapsize = 0;
    fill(head + 1, head + n + 1, 0);
    fill(where + 1, where + n + 1, -1);
    fill(dis + 1, dis + n + 1, INT_MAX);
}//初始化
void addEdge(int u, int v, int w) 
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    wei[cnt] = w;
    head[u] = cnt++;
}//链式前向星建图
void swapheap(int i,int j)
{
    swap(heap[i],heap[j]);
    where[heap[i]]=i;
    where[heap[j]]=j;
}//交换堆结构
void inheap(int i)//进堆(保持小顶堆)
{
    while(i>0&&dis[heap[i]]<dis[heap[(i-1)/2]])//比父节点距离小
    {
        swapheap(i,(i-1)/2);
        i=(i-1)/2;
    }
}
void heapify(int i)
{
    int l=1;
    while(l<heapsize)
    {
        int best=l+1<heapsize&&dis[heap[l+1]]<dis[heap[l]]?l+1:l;
        if(dis[heap[i]]<=dis[heap[best]])best=i;
        if(best==i)break;
        swapheap(best,i);
        i=best;
        l=i*2+1;
    }
}
int popheap()
{
    int ans=heap[0];
    swapheap(0,--heapsize);//让最后一个结点来到头结点
    heapify(0);
    where[ans]=-2;
    return ans;
}
void dijkstra(int v,int c)//v：结点  c:距离
{
    if(where[v]==-1)//该结点没进过堆
    {
        heap[heapsize]=v;
        where[v]=heapsize++;
        dis[v]=c;
        inheap(where[v]);
    }
    else if(where[v]>=0&&dis[v]>c)
    {
        dis[v]=c;
        inheap(where[v]);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    init(n);
    int u,v,w;
    while(m--)
    {
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }
    dijkstra(s,0);
    while(heapsize)
    {
        int v=popheap();
        for (int ei = head[v]; ei > 0; ei = nxt[ei]) 
        {
            int u = to[ei], w = wei[ei];
            if (where[u] != -2 && dis[v] + w < dis[u]) {
                dijkstra(u, dis[v] + w);
            }
        }
    }
    for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
    return 0;
}