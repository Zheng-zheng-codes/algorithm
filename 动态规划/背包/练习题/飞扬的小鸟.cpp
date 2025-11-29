//https://www.luogu.com.cn/problem/P1941
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//最大值不要取INT_MAX，会溢出
//int类型取0x3f3f3f3f    longlong类型取0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn=1e5+10;
const int maxm=1e5+10;
int updown[maxn][2];
int dp[2][maxm];
//dp[i][j]:调到第i列高度为j的最少次数
//空间压缩：每列只和前一列有关系所以只需要i&1是当前列，i&1^1是前一列
struct Tube
{
    int p,l,h;
    bool operator<(const Tube other)const
    {
        return p<other.p;
    }
}tube[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,k;cin>>n>>m>>k;
    int cnt=1;
    for(int i=1;i<=n;++i)cin>>updown[i][0]>>updown[i][1];
    for(int i=1;i<=k;++i)cin>>tube[i].p>>tube[i].l>>tube[i].h;
    sort(tube+1,tube+1+k);
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=updown[i][0];++j)dp[i&1][j]=inf;
        for(int j=updown[i][0]+1;j<=updown[i][0]+m;++j)dp[i&1][j]=min(dp[i&1][j-updown[i][0]],dp[i&1^1][j-updown[i][0]])+1;
        //完全背包：可以跳多次
        for(int j=m+1;j<=updown[i][0]+m;++j)dp[i&1][m]=min(dp[i&1][j],dp[i&1][m]);
        //题目中如果超过了上边界会停留在上边界
        for(int j=1;j<=m-updown[i][1];++j)dp[i&1][j]=min(dp[i&1][j],dp[i&1^1][j+updown[i][1]]);
        //01背包：跳与不跳
        if(i==tube[cnt].p)//验证能不能跳过管道
        {
            for(int j=0;j<=tube[cnt].l;++j)dp[i&1][j]=inf;
            for(int j=tube[cnt].h;j<=m;++j)dp[i&1][j]=inf;
            int tmp=inf;
            for(int j=tube[cnt].l+1;j<tube[cnt].h;++j)tmp=min(tmp,dp[i&1][j]);
            if(tmp==inf)
            {
                cout<<0<<'\n';
                cout<<cnt-1<<'\n';
                return 0;
            }
            cnt++;
        }
    }
    int ans=inf;
    for(int i=1;i<=m;++i)ans=min(ans,dp[n&1][i]);
    cout<<1<<'\n';
    cout<<ans<<'\n';
}