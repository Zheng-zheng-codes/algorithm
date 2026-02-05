//https://ac.nowcoder.com/acm/contest/120561/G
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans(int num)
{
    while(num%10==0)num/=10;
    int res=0;
    while(num)
    {
        res*=10;
        res+=num%10;
        num/=10;
    }
    return res;
}
void solve()
{
    int l,r;
    cin>>l>>r;
    int  res=ans(r);
    int base=1;
    int tmp=r;//最大“折叠数”就是把最后一位不断刷成9
    while(tmp)
    {
        tmp/=10;
        base*=10;
        int x=r/base*base-1;
        if(x>=l)res=max(res,ans(x));
    }
    cout<<res<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}
