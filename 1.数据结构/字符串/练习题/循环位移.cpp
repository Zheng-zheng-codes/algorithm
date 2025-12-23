//https://acm.hdu.edu.cn/showproblem.php?pid=7433
//字符串哈希
#include<bits/stdc++.h>
#define int long long
using namespace std;
int base=499;
const int maxn=5e5+10;
int tran(char c)
{
    return c-'A'+1;
}
int f[maxn];
void solve()
{
    string a,b;cin>>a>>b;
    int n=a.size();
    unordered_set<int>us;
    string s1=' '+a+a;
    string s2=' '+b;
    int n1=s1.size(),n2=s2.size();
    vector<int>h1(n1);
    h1[0]=0;
    for(int i=1;i<n1;++i)h1[i]=h1[i-1]*base+tran(s1[i]);
    vector<int>h2(n2);
    h2[0]=0;
    for(int i=1;i<n2;++i)h2[i]=h2[i-1]*base+tran(s2[i]);
    for(int i=1,j=n;j<n1;++i,++j)
    {
        int num=h1[j]-h1[i-1]*f[j-i+1];//子串哈希值公式
        us.insert(num);
    }
    int ans=0;
    for(int i=1,j=n;j<n2;++i,++j)
    {
        int num=h2[j]-h2[i-1]*f[j-i+1];
        if(us.count(num))ans++;
    }
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    f[0]=1;
    for(int i=1;i<maxn;++i)f[i]=f[i-1]*base;
    while(t--)solve();
}