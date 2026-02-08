#include<iostream>
#include<vector>
using namespace std;
const int maxn=2e4+10;
vector<int>tu[maxn];
int siz[maxn];
bool jud[maxn];
vector<int>res;
int best;
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
    if(maxsiz==best)res.push_back(node);
    else if(maxsiz<best)
    {
        best=maxsiz;
        res.clear();
        res.push_back(node);
    }
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        jud[i]=0;
        siz[i]=0;
        res.clear();
        best=maxn;
    }
    for(int i=0;i<n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    dfs(1);
    for(int i=0;i<res.size();++i)cout<<res[i]<<' ';
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}