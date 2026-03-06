//https://codeforces.com/gym/105537/problem/J
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n,m;cin>>n>>m;
    int cnt=0;
    for(int i=0;i<m;++i)
    {
        int u,v;cin>>u>>v;
        if(u<v)cnt++;
        //统计有多少条边u<v
        //如果这样的边超过了[m/2]条，就把其他边(v>u)全部反向得到拓扑序1,2,3,……
        //否则把这些边都反向，得到n,n-1,n-2,……
    }
    if(cnt>=(m+1)/2)
    {
        for(int i=1;i<=n;++i)cout<<i<<' ';
        cout<<'\n';
    }
    else
    {
        for(int i=n;i>=1;--i)cout<<i<<' ';
        cout<<'\n';  
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}