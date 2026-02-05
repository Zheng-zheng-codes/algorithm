//https://www.luogu.com.cn/problem/P6487
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    vector<int>dp;
    dp.push_back(1);
    dp.push_back(2);
    int num1=1,num2=2;
    int sum=2;
    while(sum<=n)
    {
        int tmp=num1+num2;
        num1=num2;
        num2=tmp;
        dp.push_back(tmp);
        sum=tmp;
    }
    int ans=n;
    while(1)
    {
        int idx=lower_bound(dp.begin(),dp.end(),ans)-dp.begin();
        if(ans==dp[idx])
        {
            cout<<ans<<'\n';
            break;
        }
        else ans-=dp[idx-1];
    }
}