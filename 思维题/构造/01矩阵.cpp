//https://ac.nowcoder.com/acm/contest/120562/E
//先构建左上三角矩阵，之后从右往左把每一行的1变成列
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int m[maxn][maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n-i;++j)
        {
            m[i][j]=1;
        }
    }
    for(int i=2;i<=n;i+=2)
    {
        for(int j=1;j<=n;++j)
        {
            if(m[i][j]==0)break;
            m[n-j+1][n-i+1]=m[i][j];
            m[i][j]=0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            cout<<m[i][j];
        }
        cout<<'\n';
    }
}