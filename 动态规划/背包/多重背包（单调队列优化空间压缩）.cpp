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
    for(int i=1;i<=n;i++)
    {
        int val=thing[i][0],wei=thing[i][1],cnt=thing[i][2];
        for(int mod=0;mod<wei;mod++)//每个对应价值的下标按照余数处理
        //几个余数相同的上一列的数决定这一列的数
        {
            deque<int>dq;//单调队列存储下标
            //单调队列比较的是这个值
            auto value=[&](int idx)
            {
                return dp[idx]-(idx/wei)*val;
            };
            for(int j=w-mod,c=1;j>=0&&c<=cnt;j-=wei,c++)//先将前cnt个数放入单调队列
            {
                while(!dq.empty()&&value(dq.back())<=value(j))dq.pop_back();
                dq.push_back(j);
                if(dq.front()==j-wei*(cnt+1))dq.pop_front();
            }
            //out当前要出去的值   in：当前要进入的值
            for(int out=w-mod,in=w-mod-wei*cnt;out>=0;out-=wei,in-=wei)
            {
                if(in>=0)//还有值能进入
                {
                    while(!dq.empty()&&value(dq.back())<=value(in))dq.pop_back();
                    dq.push_back(in);
                }
                dp[out]=value(dq.front())+(out/wei)*val;//更新当前值
                if(out==dq.front())dq.pop_front();//过期退出
            }
        }
    }
    cout<<dp[w];
    return 0;
}