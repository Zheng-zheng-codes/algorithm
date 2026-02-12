//https://www.luogu.com.cn/problem/P3304
//先得到一条直径，并从最后一个点开始记录不走当前直径的最长路径
//如果这个最长路径等于直径中后半段的路径，则当前节点处有另一条直径（可以把右边界压缩到这里）
//如果这个最长路径第一次等于直径中前半段的路径，左边界就在这里
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
const int maxn=2e5+10;
vector<pii>tu[maxn];
int node;
int length;
int dis[maxn];
int lst[maxn];
bool on[maxn];
int n;
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
        pii tmp=tu[now][i];
        if(tmp.first==fa)continue;
        dis[tmp.first]=dis[now]+tmp.second;
        lst[tmp.first]=now;
        dfs(tmp.first,now);
        if(dis[tmp.first]>length)
        {
            node=tmp.first;
            length=dis[tmp.first];
        }
    }
}
int dfs2(int now,int fa)
{
    int ans=0;
    for(int i=0;i<tu[now].size();++i)
    {
        pii tmp=tu[now][i];
        int v=tmp.first;
        int w=tmp.second;
        if(v==fa||on[v])continue;
        ans=max(ans,w+dfs2(v,now));
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int x,y,w;cin>>x>>y>>w;
        tu[x].push_back({y,w});
        tu[y].push_back({x,w});
    }
    init();
    dfs(1,0);
    int tmp=node;
    init();
    dfs(tmp,0);
    cout<<length<<'\n';
    int cur=node;
    vector<int>path;
    while(cur)
    {
        path.push_back(cur);
        on[cur]=1;
        cur=lst[cur];
    }
    int l=tmp,r=node;
    for(int i=1;i<path.size()-1;++i)
    {
        int nxt=path[i];
        int maxdis=dfs2(nxt,0);
        if(maxdis==length-dis[nxt])r=nxt;
        if(maxdis==dis[nxt]&&l==tmp)l=nxt;
    }
    int ans=0;
    while(r!=l)
    {
        ans++;
        r=lst[r];
    }
    cout<<ans<<'\n';
}