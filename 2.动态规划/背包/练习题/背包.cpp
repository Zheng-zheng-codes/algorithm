//https://www.luogu.com.cn/problem/P13957
//费用高的物品倾向于优先选择让它免费
//如果价值高显然成立
//如果价值低我们也倾向于用少的钱买费用高的物品
//按照费用排序，前i个物品(1<=i<=n)01背包，剩下的物品选择价值前k高的免费
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e3+10;
const int maxm=1e4+10;
int dp[maxm];
int las[maxn];
struct thing
{
    int val;
    int cost;
}t[maxn];
static bool cmp(thing a,thing b)
{
    return a.cost<b.cost;
} 
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,w,k;cin>>n>>w>>k;
    for(int i=1;i<=n;i++)cin>>t[i].cost>>t[i].val;
    sort(t+1,t+n+1,cmp);
    priority_queue<int,vector<int>,greater<int>>pq;
    int sum=0;
    for(int i=n;i>=1;i--)
    {
        sum+=t[i].val;
        pq.push(t[i].val);
        if(pq.size()>k)
        {
            int tmp=pq.top();
            pq.pop();
            sum-=tmp;
        }
        las[i]=sum;
    }
    int ans=las[1];
    for(int i=1;i<=n;i++)
    {
        for(int j=w;j>=t[i].cost;j--)
        {
            dp[j]=max(dp[j],dp[j-t[i].cost]+t[i].val);
        }
        ans=max(ans,dp[w]+las[i+1]);
    }
    cout<<ans;
}