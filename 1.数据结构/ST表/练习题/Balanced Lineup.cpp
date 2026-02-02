//https://www.luogu.com.cn/problem/P2880
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
int st1[maxn][16];//用来存储范围内最大值的ST表
int st2[maxn][16];//用来存储范围内最小值的ST表
int h[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;++i)
    {
        cin>>h[i];
        st1[i][0]=h[i];
        st2[i][0]=h[i];
    }
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i+(1<<p)-1<=n;++i)
        {
            int tmp=1<<(p-1);
            st1[i][p]=max(st1[i][p-1],st1[i+tmp][p-1]);
            st2[i][p]=min(st2[i][p-1],st2[i+tmp][p-1]);
        }
    }
    while(q--)
    {
        int a,b;cin>>a>>b;
        int tmp=(int)log2(b-a+1);
        int num1=max(st1[a][tmp],st1[b-(1<<tmp)+1][tmp]);//用两边的最值来决定范围的最值
        int num2=min(st2[a][tmp],st2[b-(1<<tmp)+1][tmp]);
        cout<<num1-num2<<'\n';
    }
}