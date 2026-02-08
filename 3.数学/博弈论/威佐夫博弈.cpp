//https://www.luogu.com.cn/problem/P2252
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ld=long double;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int a,b;
    cin>>a>>b;
    ld gold=(sqrt(5.0L)+1.0L)/2.0L;
    int minn=min(a,b);
    int maxn=max(a,b);
    int diff=maxn-minn;
    if(minn!=(int)(gold*diff))cout<<1;
    else cout<<0;
    return 0;
}