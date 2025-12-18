#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,w;//n:物品的数量  w：背包容量
    cin>>n>>w;
    vector<vector<int>>thing(n+1,vector<int>(3));
    for(int i=1;i<=n;i++)cin>>thing[i][0]>>thing[i][1]>>thing[i][2];
    //thing[i][0]:物品的价值
    //thing[i][1]:物品的重量
    //thing[i][2]:物品的数量
    vector<int>dp(w+1,0);
    //dp[i][j]:买前i种商品，容量不超过j且数量不超的最大价值
    for(int i=1;i<=n;i++)
    {
        for(int j=w;j>=0;j--)
        {
            for(int k=1;k<=thing[i][2]&&j-k*thing[i][1]>=0;k++)
            {
                dp[j]=max(dp[j],dp[j-k*thing[i][1]]+k*thing[i][0]);
            }
        }
    }
    cout<<dp[w];
}