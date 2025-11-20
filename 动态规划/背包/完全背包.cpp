#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t,m;
    cin>>t>>m;//t:背包容量  m：物品数量
    vector<vector<int>>thing(m+1,vector<int>(2));
    for(int i=1;i<=m;i++)cin>>thing[i][0]>>thing[i][1];
    //thing[i][0]:物品的消耗    thing[i][1]:物品的价值
    vector<vector<int>>dp(m+1,vector<int>(t+1,0));
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=thing[i][0])dp[i][j]=max(dp[i][j],dp[i][j-thing[i][0]]+thing[i][1]);
        }
    }
    cout<<dp[m][t];
    return 0;
}