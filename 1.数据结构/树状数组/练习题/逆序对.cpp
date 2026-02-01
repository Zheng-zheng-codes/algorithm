//https://www.luogu.com.cn/problem/P1908
//本题还可以用归并分治解决，详见思维题
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
int a[maxn];
int tree[maxn];
int n;
void add(int pos,int num)
{
    while(pos<=n)
    {
        tree[pos]+=num;
        pos+=pos&(-pos);
    }
}
int sum(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    int ans=0;
    for(int i=n;i>=1;--i)
    {
        ans+=sum(a[i]-1);
        add(a[i],1);
    }
    cout<<ans;
}