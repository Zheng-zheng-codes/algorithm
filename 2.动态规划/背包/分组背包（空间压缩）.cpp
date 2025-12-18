#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int m,n;
    cin>>m>>n;//背包大小为m,共n个物品
    vector<vector<int>>thing(n+1,vector<int>(3));
    //每个物品的重量、价值、所在组
    for(int i=1;i<=n;i++)cin>>thing[i][0]>>thing[i][1]>>thing[i][2];
    sort(thing.begin()+1,thing.end(),[](const vector<int>&a,const vector<int>&b){
        return a[2]<b[2];
    });
    //统计一共有多少组
    int teams=1;
    for(int i=2;i<=n;i++)
    {
        if(thing[i][2]!=thing[i-1][2])teams++;
    }
    vector<int>dp(m+1,0);
    for(int i=1,st=1,en=2;st<=n;i++)//st和en表示这一组的物品收尾位置
    {
        while(en<=n&&thing[en][2]==thing[st][2])en++;
        for(int j=m;j>=0;j--)
        {
            for(int k=st;k<en;k++)
            {
                if(j>=thing[k][0])//分别尝试放每一种物品
                {
                    dp[j]=max(dp[j],dp[j-thing[k][0]]+thing[k][1]);
                }
            }
        }
        st=en++;
    }
    cout<<dp[m];
    return 0;
}