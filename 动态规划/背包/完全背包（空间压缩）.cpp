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
    vector<int>dp(t+1,0);
    for(int i=1;i<=m;i++)
    {
        for(int j=thing[i][0];j<=t;j++)
        {
            dp[j]=max(dp[j],dp[j-thing[i][0]]+thing[i][1]);
        }
    }
    cout<<dp[t];
    return 0;
}