//https://ac.nowcoder.com/acm/contest/120562/H
//对于一个数组，遇见ai后可以认为从上一个ai的下一个元素开始到这个ai作为子数组的左端点，右端点为从这个ai开始一直到结尾的端点
//对于这些子数组计算ai的贡献，对于每个左端点来说ai的贡献是1+2+…+(n-i+1)
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int a[maxn];
void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    unordered_map<int,int>um;
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        if(!um.count(a[i]))
        {
            ans+=i*(1+n-i+1)*(n-i+1)/2;
            um[a[i]]=i;
        }
        else 
        {
            int j=um[a[i]];
            ans+=(i-j)*(1+n-i+1)*(n-i+1)/2;
            um[a[i]]=i;
        }
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