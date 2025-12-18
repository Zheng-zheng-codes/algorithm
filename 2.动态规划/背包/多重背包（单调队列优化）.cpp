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
    vector<vector<int>>dp(n+1,vector<int>(w+1,0));
    //dp[i][j]:买前i种商品，容量不超过j且数量不超的最大价值
    for(int i=1;i<=n;i++)
    {
        int val=thing[i][0],wei=thing[i][1],cnt=thing[i][2];
        for(int mod=0;mod<wei;mod++)//每个对应价值的下标按照余数处理
        //几个余数相同的上一列的数决定这一列的数
        {
            deque<int>dq;//单调队列存储下标
            for(int j=mod;j<=w;j+=wei)
            {
                //单调队列比较的是这个值
                auto value=[&](int idx)
                {
                    return dp[i-1][idx]-(idx/wei)*val;
                };
                while(!dq.empty()&&value(dq.back())<=value(j))dq.pop_back();
                dq.push_back(j);
                //由于只会弹出一个元素，所以直接这样判断就可以了
                if(dq.front()==j-wei*(cnt+1))dq.pop_front();
                dp[i][j]=value(dq.front())+(j/wei)*val;
            }
        }
    }
    cout<<dp[n][w];
    return 0;
}