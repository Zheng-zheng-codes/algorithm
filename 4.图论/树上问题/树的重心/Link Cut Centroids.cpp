//https://codeforces.com/problemset/problem/1406/C
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
vector<int>tu[maxn];
int siz[maxn];
int n;
int best;
vector<int>res;
void dfs(int node,int fa)
{
    siz[node]=1;
    int ms=0;
    for(int i=0;i<tu[node].size();++i)
    {
        int tmp=tu[node][i];
        if(tmp==fa)continue;
        dfs(tmp,node);
        siz[node]+=siz[tmp];
        ms=max(ms,siz[tmp]);
    }
    ms=max(ms,n-siz[node]);
    if(ms<best)
    {
        res.clear();
        res.push_back(node);
        best=ms;
    }
    else if(ms==best)res.push_back(node);
}
pii dfs2(int node,int fa)
{
    if(tu[node].size()==1)return {fa,node};
    for(int i=0;i<tu[node].size();++i)
    {
        int tmp=tu[node][i];
        if(tmp==fa)continue;
        return dfs2(tmp,node);
    }
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i)tu[i].clear();
    for(int i=0;i<n-1;++i)
    {
        int x,y;cin>>x>>y;
        tu[x].push_back(y);
        tu[y].push_back(x);
    }
    res.clear();
    best=INT_MAX;
    for(int i=1;i<=n;++i)siz[i]=0;
    dfs(1,0);
    if(res.size()==1)
    //对于只有一个重心的情况，删除重心连接的一条边再加回来
    //题目要求：闲得蛋疼
    {
        int tmp=res[0];
        cout<<tmp<<' '<<tu[tmp][0]<<'\n';
        cout<<tmp<<' '<<tu[tmp][0]<<'\n';
    }
    else 
    //对于两个重心的情况，两个重心互为对方最大子树的根节点
    //删掉其中一个重心最大子树的一个叶节点连到另一个重心上即可
    {
        int tmp1=res[0],tmp2=res[1];
        pii tmp=dfs2(tmp2,tmp1);
        cout<<tmp.first<<' '<<tmp.second<<'\n';
        cout<<tmp1<<' '<<tmp.second<<'\n';
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}