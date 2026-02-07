//https://www.lanqiao.cn/problems/2085/learning/?page=1&first_category_id=1
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=1e6+10;
int a[maxn];
int dp[maxn];
int qpow(int a,int b)
{
    if(b==0)return 1;
    int tmp=qpow(a,b>>1);
    tmp=1LL*tmp*tmp%mod;
    if(b&1)return 1LL*tmp*a%mod;
    else return tmp;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        int x,y;cin>>x>>y;
        int tmp=qpow(y,mod-2);
        a[i]=1LL*(y-x)*tmp%mod;
    }
    for(int i=1;i<=n;++i)
    {
        dp[i]=(dp[i-1]+1)%mod*1LL*qpow(a[i],mod-2)%mod;
    }
    cout<<dp[n];
}