//https://www.luogu.com.cn/problem/P1637
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e4+10;
int a[maxn];
int tree[maxn];
int tree2[maxn];
int res[maxn][2];
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
void add2(int pos,int num)
{
    while(pos<=n)
    {
        tree2[pos]+=num;
        pos+=pos&(-pos);
    }
}
int sum2(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=tree2[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    vector<int>tmp;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        tmp.push_back(a[i]);
    }
    sort(tmp.begin(),tmp.end());
    int cnt=unique(tmp.begin(),tmp.end())-tmp.begin();
    unordered_map<int,int>um;
    for(int i=0;i<cnt;++i)um[tmp[i]]=i+1;
    for(int i=n;i>=1;--i)
    {
        res[i][0]=(n-i)-sum(um[a[i]]);
        add(um[a[i]],1);
    }
    for(int i=1;i<=n;++i)
    {
        res[i][1]=sum2(um[a[i]]-1);
        add2(um[a[i]],1);
    }
    int ans=0;
    for(int i=1;i<=n;++i)ans+=res[i][0]*res[i][1];
    cout<<ans;
}