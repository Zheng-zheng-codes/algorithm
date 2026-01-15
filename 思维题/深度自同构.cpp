//https://acm.hdu.edu.cn/showproblem.php?pid=7457
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=1e6+10;
int a[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    a[1]=1;
    for(int i=2;i<=n;++i)
    {
        a[i]+=a[i-1]+1;//前面的每一种情况都加上一个共同的根节点（a[i-1]），还有一种情况所有节点都是分立的（1）
        a[i]%=mod;
        for(int j=2;i*j<=n;++j)
        {
            a[i*j]+=a[i-1];//重复几次得到结果
            a[i*j]%=mod;
        }
    }
    for(int i=1;i<=n;++i)cout<<a[i]<<' ';
}