/*
Forever-chicken 最近在学习多种单源最短路算法，例如 Dijkstra 算法、Bellman-Ford 算法等。
为了测试这些算法的正确性与效率，他按照下面的方式生成了一个包含 n 个点（编号 1 到 n）的有向图：
对每个点 i（1 ≤ i ≤ n/2），添加一条从 i 到 2·i 的有向边；
对每个点 i（1 ≤ i ≤ n/3），添加一条从 i 到 3·i 的有向边；
对每个点 i（1 ≤ i ≤ n − 1），添加一条从 i 到 i+1 的有向边；
现在他想知道：从顶点 1 到顶点 n 的最短路径长度是多少？你能帮他计算吗？
*/
//纯纯误导，根本不是图论，就是思维题
#include<bits/stdc++.h>
#define int long long
using namespace std;
unordered_map<int,int>dp;
int dfs(int n)
{
    if(dp.count(n))return dp[n];
    int ans=LLONG_MAX;
    ans=min(ans,dfs(n/2)+1+n%2);
    ans=min(ans,dfs(n/3)+1+n%3);
    dp[n]=ans;
    return ans;
}
void solve()
{
    int n;cin>>n;
    dp[0]=dp[1]=0;
    cout<<dfs(n)<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}