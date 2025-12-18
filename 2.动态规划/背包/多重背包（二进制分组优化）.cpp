#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
//从1开始把物品的数量分成几个2的幂次的形式
//如13=1+2+4+6（最后6个构不成2^3）把一个物品拆分成这样的几个物品进行01背包
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,w;
    cin>>n>>w;
    vector<pii>thing;
    int siz=0;//物品的数量
    while(n--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        for(int i=1;c>0;i*=2)
        {
           if(c>=i)
           {
                thing.emplace_back(a*i,b*i);
                c-=i;
                siz++;
           }
            else
            {
                thing.emplace_back(a*c,b*c);
                siz++;
                break;
            }
        }
    }
    vector<int>dp(w+1,0);
    for(int i=0;i<siz;i++)
    {
        int val=thing[i].first;
        int cost=thing[i].second;
        for(int j=w;j>=cost;j--)
        {
            dp[j]=max(dp[j],dp[j-cost]+val);
        }
    }
    cout<<dp[w];
    return 0;
}