//https://www.luogu.com.cn/problem/P2195
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int fa[maxn];
int siz[maxn];
//用来存储每一个连通块的直径大小：只有头结点的这个值是有效的
vector<int>tu[maxn];
void init(int n)
{
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
        siz[i]=0;
    }
}
int find(int n)
{
    if(n==fa[n])return n;
    fa[n]=find(fa[n]);
    return fa[n];
}
void unit(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy)return;
    fa[fy]=fx;
    int num=max(siz[fx],siz[fy]);
    num=max(num,1+(siz[fx]+1)/2+(siz[fy]+1)/2);
    siz[fx]=num;
}
int dis[maxn];
int ans[maxn];
int res;
void dp(int node,int fa)
{
    for(int i=0;i<tu[node].size();++i)
    {
        int tmp=tu[node][i];
        if(tmp==fa)continue;
        dp(tmp,node);
        int length=dis[tmp]+1;
        ans[node]=max(ans[node],length+dis[node]);
        dis[node]=max(dis[node],length);
    }
    res=max(res,ans[node]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,q;cin>>n>>m>>q;
    init(n);
    while(m--)
    {
        int x,y;cin>>x>>y;
        tu[x].push_back(y);
        tu[y].push_back(x);
        int fx=find(x),fy=find(y);
        if(fx!=fy)fa[fy]=fx;
    }
    //求最初每一个连通块的直径大小
    for(int i=1;i<=n;++i)
    {
        if(fa[i]==i)
        {
            dp(i,0);
            siz[i]=res;
            res=0;
        }
    }
    while(q--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x;cin>>x;
            int fx=find(x);
            cout<<siz[fx]<<'\n';
        }
        //合并以后要让新的直径最小
        //合成的直径大小是两个直径大小除以2的和再加1
        //当然也可能是原来的直径大小，三个数取最大值
        else
        {
            int x,y;cin>>x>>y;
            unit(x,y);
        }
    }
}