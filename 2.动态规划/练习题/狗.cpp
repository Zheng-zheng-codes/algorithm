//https://www.cnblogs.com/jinjiaqioi/p/17743573.html
/*
题目描述
小G养了很多狗。
小G一共有 n×n 条狗，在一个矩阵上。小G想让狗狗交朋友，一条狗狗最多只能交一个朋友，不必所有狗狗都有朋友。
但是狗狗交朋友有要求，具体的，第 i 行第 j 列的狗有两个值 di,j∈{U,D,L,R} 表示它只能和上/下/左/右的狗狗交朋友，如果成功交友能得到 ai,j的喜悦值。
一个交友方案的价值就是所有有朋友的狗狗的喜悦值之和。
小G想知道所有交友方案的价值和，由于这个数可能很大，请对 998244353 取模并告诉小G。
朋友关系是双向的,两条狗互相交朋友需要两个d都满足,上下左右不必相邻
上下左右是指正上/正下/正左/正右，也就是要在同一行同一列
输入描述
第一行一个整数 n。
接下来 n 行每行一个长度为 n 的字符串，第 i 行 j 列的字符表示 di,j。
接下来 n 行每行 n 个数字，第 i 行第 j 个表示 ai,j。
输出描述
一行一个整数表示对 998244353 取模的结果。
n<=500
*/

//每一行和每一列都是相互独立的，所以可以单独拿出来讨论
//最后如果把所有方案数相乘就是总方案数，如果针对某一个方案，就要除掉这个方案的方案数，再乘对应的幸福值
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=502;
int qpow(int a,int b)
{
    int r=1;
    while(b)
    {
        if(b&1) r=1LL*r*a%mod;
        a=1LL*a*a%mod;
        b>>=1;
    }
    return r;
}
string d[maxn];//用来存储每只狗的状态
int a[maxn][maxn];//用来存储每只狗的喜悦值
int f[maxn][maxn];//f[i][j]:前i条狗中有j条R/D狗没有匹配时的方案数
int g[maxn][maxn];//g[i][j]:前i条狗中有j条R/D狗没有匹配时的权值和
int cnt;
int p[maxn<<1];//用来存储每一行/列的方案数
int q[maxn<<1];//用来存储每一行/列的权值和
char c[maxn];//把每一行/列相关的字符单独挑出来
int c2[maxn];//把每一行/列相关的幸福值单独挑出来
int n;
int cnt2;
void solve()
{
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    f[0][0]=1;
    for(int i=1;i<=cnt;++i)
    {
        for(int j=0;j<=i;++j)
        {
			//不选直接加
            f[i][j]=(f[i][j]+f[i-1][j])%mod;
            g[i][j]=(g[i][j]+g[i-1][j])%mod;
			//遇见'L'或'U'选
            if(c[i]=='L'||c[i]=='U')
            {
                if(j)
                {
                    f[i][j-1]=(f[i][j-1]+1LL*f[i-1][j]*j%mod)%mod;
                    g[i][j-1]=((g[i][j-1]+1LL*g[i-1][j]*j%mod)%mod+1LL*f[i-1][j]*c2[i]%mod*j%mod)%mod;
                }
            }
			//遇见'R'或'D'准备选
            else
            {
                f[i][j+1]=(f[i][j+1]+f[i-1][j])%mod;
                g[i][j+1]=((g[i][j+1]+g[i-1][j])%mod+1LL*f[i-1][j]*c2[i]%mod)%mod;
            }
        }
    }
    p[++cnt2]=f[cnt][0];
    q[cnt2]=g[cnt][0];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=0;i<n;++i)cin>>d[i];
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin>>a[i][j];
        }
    }
    for(int i=0;i<n;++i)
    {
        cnt=0;
        for(int j=0;j<n;++j)
        {
            if(d[i][j]=='L'||d[i][j]=='R')
            {
                c[++cnt]=d[i][j];
                c2[cnt]=a[i][j];
            }
        }
        if(cnt)solve();
        cnt=0;
        for(int j=0;j<n;++j)
        {
            if(d[j][i]=='U'||d[j][i]=='D')
            {
                c[++cnt]=d[j][i];
                c2[cnt]=a[j][i];
            }
        }
        if(cnt)solve();
    }
    int ans=0;
    int tmp=1;
    for(int i=1;i<=cnt2;++i)tmp=(1LL*tmp*p[i])%mod;
    for(int i=1;i<=cnt2;++i)ans=(ans+1LL*q[i]*tmp%mod*qpow(p[i],mod-2)%mod)%mod;
    cout<<ans<<'\n';
}