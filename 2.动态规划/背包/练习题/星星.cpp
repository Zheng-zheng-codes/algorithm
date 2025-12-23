//https://acm.hdu.edu.cn/showproblem.php?pid=7434
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>dp(k+1,0x3f3f3f3f);
    dp[0]=0;
    vector<vector<int>>things(n+1,vector<int>(5));
    for(int i=1;i<=n;++i)cin>>things[i][1]>>things[i][2]>>things[i][3]>>things[i][4];
    for(int i=1;i<=n;++i)
    {
        for(int j=k;j>=1;--j)
        {
            for(int tmp=1;tmp<=4;++tmp)
            {
                if(j<tmp)break;
                dp[j]=min(dp[j-tmp]+things[i][tmp],dp[j]);
            }
        }
    }
    cout<<dp[k]<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}