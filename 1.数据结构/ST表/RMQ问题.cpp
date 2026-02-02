//https://www.luogu.com.cn/problem/P3865
//ST表适合的问题：可重复贡献问题
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int st[maxn][17];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)st[i][0]=a[i];
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i+(1<<p)-1<=n;++i)
        {
            int tmp=1<<(p-1);
            st[i][p]=max(st[i][p-1],st[i+tmp][p-1]);
        }
    }
    while(m--)
    {
        int l,r;cin>>l>>r;
        int tmp=(int)log2(r-l+1);
        cout<<max(st[l][tmp],st[r-(1<<tmp)+1][tmp])<<'\n';
    }
}