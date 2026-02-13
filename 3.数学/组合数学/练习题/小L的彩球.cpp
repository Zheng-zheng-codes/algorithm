//https://ac.nowcoder.com/acm/contest/120566/B
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=1e6+10;
int fac[maxn];
int inv[maxn];
int qpow(int a,int b)
{
    if(b==0)return 1;
    int tmp=qpow(a,b>>1);
    tmp=tmp*tmp%mod;
    if(b&1)return tmp*a%mod;
    else return tmp;
}
void init()
{
    fac[0]=1;
    for(int i=1;i<maxn;i++)fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for(int i=maxn-1;i>=1;i--)inv[i-1]=inv[i]*i%mod;
}
int C(int n,int m)
{
    if(n<0||m<0||m>n) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void solve()
{
    int n,x,t;cin>>n>>x>>t;
    if(t==0)
    {
        if(n==x)cout<<1<<'\n';
        else cout<<0<<'\n';
        return;
    }
    //如果把放在左边盒子视为0，右边盒子视为1，得到一个01序列，连续的0或1一共有t+1个区域
    int k=t+1;
    int ans=0;
    int zero=(k+1)/2;//从0开始（1号球放在左边）
    int one=k/2;
    if(x>=zero&&n-x>=one)ans=(ans+C(x-1,zero-1)*C(n-x-1,one-1)%mod)%mod;
    //使用隔板法：左边盒子x个球分成zero份，右边盒子n-x个球分成one份
    zero=k/2;//从1开始（1号球放在右边）
    one=(k+1)/2;
    if(x>=zero&&n-x>=one)ans=(ans+C(x-1,zero-1)*C(n-x-1,one-1)%mod)%mod;
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t=1;cin>>t;
    init();
    while(t--)solve();
}