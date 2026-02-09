//http://poj.org/problem?id=3107
//树的重心第二种求法：每棵子树的节点数都不超过所有节点数的一半
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=2e4+10;
vector<int>tu[maxn];
int siz[maxn];
bool jud[maxn];
vector<int>res;
int n;
void dfs(int node)
{
    siz[node]=1;
    jud[node]=1;
    int maxsiz=0;
    for(int i=0;i<tu[node].size();++i)
    {
        int tmp=tu[node][i];
        if(jud[tmp])continue;
        dfs(tmp);
        siz[node]+=siz[tmp];
        maxsiz=max(maxsiz,siz[tmp]);
    }
    maxsiz=max(maxsiz,n-siz[node]);
    if(maxsiz<=n/2)res.push_back(node);
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        jud[i]=0;
        siz[i]=0;
        tu[i].clear();
    }
    res.clear();
    for(int i=0;i<n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    dfs(1);
    sort(res.begin(),res.end());
    for(int i=0;i<res.size();++i)cout<<res[i]<<' ';
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t=1;//cin>>t;
    while(t--)solve();
}