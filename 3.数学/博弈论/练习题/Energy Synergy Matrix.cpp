//https://ac.nowcoder.com/acm/contest/120563/F
//要走的次数即为n-1加上拐弯的次数
//小红先手会往小小红不在的行上下障碍物（不让她拐弯），小紫会往小红在的那一行下障碍物
//由此可得每五列就会拐一下弯
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;cin>>n;
    cout<<n-1+n/5<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}