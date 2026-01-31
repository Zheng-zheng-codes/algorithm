//https://atcoder.jp/contests/abc443/tasks/abc443_d
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+10;
int r[maxn];
int x[maxn];
void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>r[i];
        x[i]=r[i];
    }
    for(int i=2;i<=n;++i)x[i]=min(x[i],x[i-1]+1);
    for(int i=n-1;i>=1;--i)x[i]=min(x[i],x[i+1]+1);
    int ans=0;
    for(int i=1;i<=n;++i)ans+=r[i]-x[i];
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}