#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t,m;//t：背包容量    m：物品数量
    cin>>t>>m;
    vector<vector<int>>dp(m+1,vector<int>(t+1));
    //dp[i][j]:前i个物品用容量为j的背包装的最大价值
    vector<vector<int>>thing(m+1,vector<int>(2));
    //thing[i][0]:i物品的花费
    //thing[i][1]:i物品的价值
    for(int i=1;i<=m;i++)cin>>thing[i][0]>>thing[i][1];
    for(int i=0;i<=m;i++)dp[i][0]=0;
    for(int j=0;j<=t;j++)dp[0][j]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=t;j++)
        {
            if(j<thing[i][0])dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-thing[i][0]]+thing[i][1]);
        }
    }
    cout<<dp[m][t];
    return 0;
}