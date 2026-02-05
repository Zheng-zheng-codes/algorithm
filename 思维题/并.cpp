//https://acm.hdu.edu.cn/showproblem.php?pid=7444
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
struct rect
{
    int x1,y1,x2,y2;
};
int qpow(int a,int b)
{
    long long base = a % mod;
    long long res = 1;
    long long e = b;
    while(e > 0)
    {
        if(e & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        e >>= 1;
    }
    return (int)res;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    vector<rect>rects(n);
    vector<int>xx;
    vector<int>yy;
    for(int i=0;i<n;++i)
    {
        cin>>rects[i].x1>>rects[i].y1>>rects[i].x2>>rects[i].y2;
        xx.push_back(rects[i].x1);
        xx.push_back(rects[i].x2);
        yy.push_back(rects[i].y1);
        yy.push_back(rects[i].y2);
    }
    sort(xx.begin(),xx.end());
    auto itx=unique(xx.begin(),xx.end());
    xx.erase(itx,xx.end());
    sort(yy.begin(),yy.end());
    auto ity=unique(yy.begin(),yy.end());
    yy.erase(ity,yy.end());
    int X=xx.size(),Y=yy.size();
    vector<vector<int>>diff(X+1,vector<int>(Y+1,0));
    for(int i=0;i<n;++i)
    {
        int x1=lower_bound(xx.begin(),xx.end(),rects[i].x1)-xx.begin();
        int x2=lower_bound(xx.begin(),xx.end(),rects[i].x2)-xx.begin();
        int y1=lower_bound(yy.begin(),yy.end(),rects[i].y1)-yy.begin();
        int y2=lower_bound(yy.begin(),yy.end(),rects[i].y2)-yy.begin();
        diff[x1][y1]++;
        diff[x2][y1]--;
        diff[x1][y2]--;
        diff[x2][y2]++;
    }
    vector<vector<int>>C(n+1,vector<int>(n+1,0));
    for(int i=0;i<=n;++i)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    vector<int>sumArea(n+1,0);
    for(int i=0;i<X;++i)
    {
        for(int j=0;j<Y;++j)
        {
            int cur=diff[i][j];
            if(i>0)cur+=diff[i-1][j];
            if(j>0)cur+=diff[i][j-1];
            if(i>0&&j>0)cur-=diff[i-1][j-1];
            diff[i][j]=cur;
            if(i<X-1&&j<Y-1&&cur>0)
            {
                long long w = (xx[i+1] - xx[i]) % mod;
                long long h = (yy[j+1] - yy[j]) % mod;
                long long area = (w * h) % mod;
                sumArea[cur] = (sumArea[cur] + (int)area) % mod;
            }
        }
    }
    for(int k=1;k<=n;++k)
    {
        int ans = 0;
        for(int j=1;j<=n;++j)
        {
            if(sumArea[j]==0) continue;
            int ways = C[n][k];
            if(n - j >= k) ways = (ways - C[n-j][k] + mod) % mod;
            ans = (ans + sumArea[j] * ways) % mod;
        }
        ans = ans * qpow(C[n][k], mod-2) % mod;
        cout << ans << '\n';
    }
    return 0;
}
