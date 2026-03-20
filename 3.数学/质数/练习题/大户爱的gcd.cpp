//https://acm.hdu.edu.cn/contest/problem?cid=1197&pid=1008
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int arr[maxn];//每个节点的值一定是所有g值的最小公倍数的整数倍，这里存储最小公倍数
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}
void solve()
{
    int n,m,q;cin>>n>>m>>q;
    for(int i=1;i<=n;++i)arr[i]=1;
    for(int i=0;i<m;++i)
    {
        int x,y,g;cin>>x>>y>>g;
        arr[x]=arr[x]/gcd(arr[x],g)*g;
        arr[y]=arr[y]/gcd(arr[y],g)*g;
    }
    while(q--)
    {
        int x,y;cin>>x>>y;
        cout<<gcd(arr[x],arr[y])<<'\n';
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}