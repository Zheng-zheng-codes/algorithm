//https://www.luogu.com.cn/problem/P3388
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+10;
vector<int>tu[maxn];
bool jud[maxn];//判断是否遍历过
int dfn[maxn];//dfs树的序列号
int low[maxn];//当前节点和通过回边能走到的最小dfn
bool iscut[maxn];//判断是不是割点
int cnt;
void init(int n)
{
    cnt=1;
    for(int i=1;i<=n;i++)
    {
        tu[i].clear();
        jud[i]=0;
        iscut[i]=0;
    }
}
void dfs(int v,int fa)
{
    dfn[v]=low[v]=cnt++;//low先定为dfn
    jud[v]=1;
    int n=0;
    for(int i=0;i<tu[v].size();i++)
    {
        int nxt=tu[v][i];
        if(!jud[nxt])
        {
            n++;
            dfs(nxt,v);
            low[v]=min(low[v],low[nxt]);//后面的节点往回走了一次
            if(fa!=-1&&low[nxt]>=dfn[v])iscut[v]=1;
            //当有一个子树往回走不过当前节点那么这个点连接它和前面的点，所以说去掉这个点就不连通了
        }
        else if(nxt!=fa)low[v]=min(low[v],dfn[nxt]);//自己往回走一次
    }
    if(fa==-1&&n>=2)iscut[v]=1;
    //根节点只要有2个及以上儿子就一定是割点
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
        tu[b].push_back(a);
    }
    vector<int>ans;
    for(int i=1;i<=n;i++)
    {
        if(!jud[i])dfs(i,-1);
    }
    for(int i=1;i<=n;i++)
    {
        if(iscut[i])ans.push_back(i);
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(int i=0;i<ans.size();i++)cout<<ans[i]<<' ';
}
//求割边的问题大同小异，子节点的low大于当前节点就有割边