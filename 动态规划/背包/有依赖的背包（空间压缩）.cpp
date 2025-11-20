//https://www.luogu.com.cn/problem/P1064
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e4;//钱数的最大值
const int maxm=65;//物品数
int val[maxm];//每件物品的价值
int cost[maxm];//每件物品的花费
bool king[maxm];//每件物品是不是主件
int fans[maxm];//每件物品的附件数
int follows[maxm][2];//每件物品的附件的编号（题目规定只能最多有两个附件）
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;//n是钱数   m是物品数
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        val[i]=a*b;
        cost[i]=a;
        if(c==0)king[i]=1;
        else follows[c][fans[c]++]=i;
    }
    vector<int>dp(n+1,0);
    for(int i=1;i<=m;i++)
    {
        if(!king[i])continue;//附件在主件中处理
        for(int j=n;j>=1;j--)//五种展开方式
        {
            //第一种情况不买主件就是dp[j]本身
            if(j>=cost[i])dp[j]=max(dp[j],dp[j-cost[i]]+val[i]);//第二种情况：只买主件
            int fan1 = fans[i] >= 1 ? follows[i][0] : -1;//第一个附件
            int fan2 = fans[i] >= 2 ? follows[i][1] : -1;//第二个附件
            if(fan1!=-1&&j>=cost[i]+cost[fan1])
            dp[j]=max(dp[j],dp[j-cost[i]-cost[fan1]]+val[i]+val[fan1]);
            //第三种情况：只买第一个附件
            if(fan2!=-1&&j>=cost[i]+cost[fan2])
            dp[j]=max(dp[j],dp[j-cost[i]-cost[fan2]]+val[i]+val[fan2]);
            //第四种情况：只买第二个附件
            if(fan1!=-1&&fan2!=-1&&j>=cost[i]+cost[fan1]+cost[fan2])
            dp[j]=max(dp[j],dp[j-cost[i]-cost[fan1]-cost[fan2]]+val[i]+val[fan1]+val[fan2]);
            //第五种情况：两个附件都买
        }
    }
    cout<<dp[n];
    return 0;
}