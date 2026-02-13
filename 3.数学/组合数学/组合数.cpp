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