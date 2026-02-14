//https://www.luogu.com.cn/problem/P3629
//k=1或2
//如果不加其他边，需要2*(n-1)次访问
//加上一条边会减去形成的环的大小再加1：找直径即可-->两次dfs
//加上两条边在基础上再减去新形成的环的大小再加1，同时还要加上重叠部分的环大小：把第一次找到的直径上的边边权变成-1再找直径-->树形dp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
vector<int>tu[maxn];
bool on[maxn];
int dis[maxn];
int lst[maxn];
int length;
int node;
int n,k;
void init()
{
    node=0;
    length=0;
    for(int i=1;i<=n;++i)
    {
        dis[i]=0;
        lst[i]=0;
    }
}
void dfs(int now,int fa)
{
    for(int i=0;i<tu[now].size();++i)
    {
        int tmp=tu[now][i];
        if(tmp==fa)continue;
        dis[tmp]=dis[now]+1;
        lst[tmp]=now;
        dfs(tmp,now);
    }
    if(dis[now]>length)
    {
        node=now;
        length=dis[now];
    }
}
int dp_dis[maxn];
int dp_ans[maxn];
void dp(int now,int fa)
{
    for(int i=0;i<tu[now].size();++i)
    {
        int tmp=tu[now][i];
        if(tmp==fa)continue;
        dp(tmp,now);
        int l=on[now]&&on[tmp]?-1:1;
        int len=dp_dis[tmp]+l;
        dp_ans[now]=max(dp_ans[now],+dp_dis[now]+len);
        dp_dis[now]=max(dp_dis[now],len);
    }
    length=max(length,dp_ans[now]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=0;i<n-1;++i)
    {
        int x,y;cin>>x>>y;
        tu[x].push_back(y);
        tu[y].push_back(x);
    }
    int ans=2*(n-1);
    init();
    dfs(1,0);
    int tmp=node;
    init();
    dfs(tmp,0);
    ans-=length-1;
    if(k==1)
    {
        cout<<ans;
        return 0;
    }
    int cur=node;
    while(cur)
    {
        on[cur]=1;
        cur=lst[cur];
    }
    length=0;
    dp(1,0);
    ans-=length-1;
    cout<<ans;
}