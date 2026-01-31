//https://www.luogu.com.cn/problem/P1114
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
int a[maxn];
int sum[maxn];
unordered_map<int,pii>um;
int main()
{
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        if(a[i]==0)a[i]=-1;
    }
    for(int i=1;i<=n;++i)sum[i]=sum[i-1]+a[i];
    int res=0;
    for(int i=1;i<=n;++i)if(sum[i]==0)res=i;
    for(int i=1;i<=n;++i)
    {
        if(!um.count(sum[i]))
        {
            pii tmp={i,-1};
            um[sum[i]]=tmp;
        }
        else um[sum[i]].second=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(!um.count(sum[i])||um[sum[i]].second==-1)continue;
        res=max(res,um[sum[i]].second-um[sum[i]].first);
    }
    cout<<res;
}