//https://acm.hdu.edu.cn/showproblem.php?pid=7440
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
    int n,k;cin>>n>>k;
    int ans=1;
    for(int i=0;i<k;++i)
    {
        if((n>>i)&1)ans*=12;
        else ans*=4;
    }
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}