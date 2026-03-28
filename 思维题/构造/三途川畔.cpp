//https://acm.hdu.edu.cn/contest/problem?cid=1198&pid=1004
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n-2;++i)cout<<1<<' ';
    cout<<2<<' '<<n+k<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}