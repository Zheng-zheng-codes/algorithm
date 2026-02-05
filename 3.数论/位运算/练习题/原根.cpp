//https://www.luogu.com.cn/problem/P13953
//a^b<=a+b
//a^b>=a-b
//g=(k*p+1)^(p-1)
//然后求g=(k*p+1)^(p-1)<=m有多少个,其实就是求有多少个k
/*
可以根据不等式的关系进行放缩
(k*p+1)^(p-1)<=(k*p+1+p-1)=(k+1)*p
如果(k+1)*p<=m,那么g=(k*p+1)^(p-1)一定小于等于m
得k<=m/p-1,也就是说当k<=m/p-1时,一定满足条件
(k*p+1)^(p-1)>=(k*p+1-(p-1))=(k-1)*p+2
如果(k-1)*p+2>m,那么g一定大于m
得k>(m-2)/p+1,也就是说当k>(m-2)/p+1时,一定不满足条件
所以,k在[0,m/p-1]均是满足条件的,在((m-2)/p+1,∞)均不满足条件,而中间的数是很少的,
因为m/p-1和(m-2)/p是一个量级,枚举只要O(1),判断一下即可
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve()
{
    int p,m;
    cin>>p>>m;
    int ans=m/p;
    for(int i=m/p;i<=(m-2)/p+1;i++)
    {
        if(((i*p+1)^(p-1))<=m)ans++;
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