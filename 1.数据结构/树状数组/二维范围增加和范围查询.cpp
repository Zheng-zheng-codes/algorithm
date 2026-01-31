//https://www.luogu.com.cn/problem/P4514
//计算a[1][1]~a[n][m]的范围和
//对于差分数组来说D[i][j]出现了(n-i+1)*(m-j+1)次
//即(n+1)*(m+1)*ΣΣD[i][j]-(m+1)*ΣΣ(D[i][j]*i)-(n+1)*ΣΣ(D[i][j]*j)+ΣΣ(D[i][j]*i*j)
//所以维护四个二维差分数组即可
#include<bits/stdc++.h>
using namespace std;
const int maxn=3000;
int n,m;
int tree1[maxn][maxn];
int tree2[maxn][maxn];
int tree3[maxn][maxn];
int tree4[maxn][maxn];
void add(int x,int y,int num)
{
    int num2=x*num;
    int num3=y*num;
    int num4=x*y*num;
    for(int i=x;i<=n;i+=i&(-i))
    {
        for(int j=y;j<=m;j+=j&(-j))
        {
            tree1[i][j]+=num;
            tree2[i][j]+=num2;
            tree3[i][j]+=num3;
            tree4[i][j]+=num4;
        }
    }
}
int sum(int x,int y)
{
    int ans=0;
    for(int i=x;i>0;i-=i&(-i))
    {
        for(int j=y;j>0;j-=j&(-j))
        {
            ans+=tree1[i][j]*(x+1)*(y+1);
            ans-=tree2[i][j]*(y+1);
            ans-=tree3[i][j]*(x+1);
            ans+=tree4[i][j];
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    char c;
    while(cin>>c)
    {
        if(c=='X')cin>>n>>m;
        else if(c=='L')
        {
            int x1,y1,x2,y2,num;
            cin>>x1>>y1>>x2>>y2>>num;
            add(x1,y1,num);
            add(x1,y2+1,-num);
            add(x2+1,y1,-num);
            add(x2+1,y2+1,num);
        }
        else
        {
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            int num1=sum(x2,y2);
            int num2=sum(x1-1,y1-1);
            int num3=sum(x1-1,y2);
            int num4=sum(x2,y1-1);
            cout<<num1+num2-num3-num4<<'\n';
        }
    }
}