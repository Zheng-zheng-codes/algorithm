//https://www.luogu.com.cn/problem/P14778
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int maxn=5050;
int dp[maxn];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,k;cin>>n>>k;
    dp[1]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=i;j>=1;--j)
        {
            dp[j]=((i-1)*dp[j]%mod+dp[j-1])%mod;
        }
    }
    cout<<dp[k];
}