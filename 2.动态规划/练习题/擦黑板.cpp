//https://ac.nowcoder.com/acm/contest/120561/H
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=998244353;
int a[maxn];
int lst[31];//用来记录每一位出现1的上一个数的位置
int dp[maxn];//dp[i]:[1~i]子数组中合法的替换数
int sum[maxn];//dp[i]的前缀和
//按位或等于和当且仅当段内所有数的二进制中1的位置不重叠
void solve()
{
    int n;cin>>n;
    memset(lst,0,sizeof(lst));
    for(int i=1;i<=n;++i)cin>>a[i];
    dp[0]=sum[0]=1;
    int L=0;//L+1~i这一段二进制没有1的位置重叠
    //dp[i]即为dp[L]到dp[i-1]的和
    //dp[j]:表示前j个随机分配的结果
    for(int i=1;i<=n;++i)
    {
        for(int b=0;b<31;++b)
        {
            if((a[i]>>b)&1)L=max(L,lst[b]);
        }
        dp[i]=sum[i-1];
        if(L>=1)dp[i]=(sum[i-1]-sum[L-1]+mod)%mod;
        sum[i]=(sum[i-1]+dp[i])%mod;
        for(int b=0;b<31;++b)
        {
            if((a[i]>>b)&1)lst[b]=i;
        }
    }
    cout<<dp[n]<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}