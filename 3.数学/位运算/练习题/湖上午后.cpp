//https://acm.hdu.edu.cn/contest/problem?cid=1198&pid=1001
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
pii choose[3]={{0,0},{0,1},{1,1}};
const int mod=998244353;
const int maxn=5e5+10;
string s,t;
int pow2[maxn];
int tran(string&str)
{
    int ans=0;
    int tmp=str.size();
    for(int i=str.size()-1;i>=0;--i)
    {
        if(str[i]=='1')ans=(ans+pow2[tmp-1-i])%mod;
    }
    return ans;
}
int f()
{
    int L=t.size();
    s=string(L-s.size(),'0')+s;
    int dp[16]={0},ndp[16]={0};
    dp[15]=1;
    for(int i=0;i<L;++i)
    {
        memset(ndp,0,sizeof(ndp));
        int sn=s[i]-'0';
        int tn=t[i]-'0';
        for(int mask=0;mask<16;++mask)
        {
            if(!dp[mask])continue;
            int ls=mask>>0&1;
            int rs=mask>>1&1;
            int lt=mask>>2&1;
            int rt=mask>>3&1;
            for(auto [a,b]:choose)
            {
                if(ls&&a<sn)continue;
                if(rs&&a>tn)continue;
                if(lt&&b<sn)continue;
                if(rt&&b>tn)continue;
                int nmask=0;
                int nls=ls&&a==sn;
                int nrs=rs&&a==tn;
                int nlt=lt&&b==sn;
                int nrt=rt&&b==tn;
                nmask=(nls<<0)|(nrs<<1)|(nlt<<2)|(nrt<<3);
                ndp[nmask]=(ndp[nmask]+dp[mask])%mod;
            }
        }
        for(int mask=0;mask<16;++mask)dp[mask]=ndp[mask];
    }
    int ans=0;
    for(int i=0;i<16;++i)ans=(ans+dp[i])%mod;
    return ans;
}
void solve()
{
    cin>>s>>t;
    int ans=(tran(t)-tran(s)+1+mod)%mod;
    cout<<(f()*2%mod-ans+mod)%mod<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    pow2[0]=1;
    for(int i=1;i<maxn;++i)pow2[i]=pow2[i-1]*2%mod;
    int q;cin>>q;
    while(q--)solve();
}