//https://acm.tju.edu.cn/problem/B1023
/*
题目描述
“海棠节”是天津大学最重要的节日之一，今年的海棠节推出了一项填字游戏，
参加活动的同学可以到相应展台领取一张填字卡，填字卡的部分内容是已经给出的，
需要在’?'处填写任意大写字母，如果最终卡片上包含"TJU"，则可以领取一份礼品。
小海棠在本科学习的过程中养成了善于思考的好习惯，她想知道对于一张填字卡，她有多少种填法可以让她拿到奖品。
输入描述
多组样例，第一行输入一个整数T，表示需要处理的样例个数。
对于每组样例，包含一行字符串，字符串中仅包含大写字母和’?’。
输出描述
对于每组样例，输出一个整数表示有多少种填法可以拿到奖品，由于最终的结果很大，请将结果模1000000007输出。
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1000000007;
int qpow(int a,int b)
{
    if(b==0)return 1;
    if(b==1)return a;
    int tmp=qpow(a,b>>1);
    tmp=tmp*tmp%mod;
    if(b&1)return tmp*a%mod;
    else return tmp;
}
int go(int j, char c)
{
    if(j==0)
    {
        if(c=='T')return 1;
        return 0;
    }
    if(j==1)
    {
        if(c=='J')return 2;
        if(c=='T')return 1;
        return 0;
    }
    if(c=='U')return 3; 
    if(c=='T')return 1;
    return 0;
}
void solve()
{
    string s;cin>>s;
    int n=s.size();
    int ans=0;
    vector<vector<int>>dp(n+1,vector<int>(3));
    //dp[i][0]:考虑前i个字符，前面i-1个字符的末尾情况是空,且保证没有"TJU"
    //dp[i][1]:考虑前i个字符，前面i-1个字符的末尾情况是"T",且保证没有"TJU"
    //dp[i][2]:考虑前i个字符，前面i-1个字符的末尾情况是"TJ",且保证没有"TJU"
    dp[0][0]=1;
    int q=0;
    for(int i=0;i<n;++i)
    {
        if(s[i]=='?')++q;
        for(int j=0;j<3;++j)
        {
            int cur=dp[i][j];
            if(!cur)continue;
            if(s[i]=='?')
            {
                for(char c='A';c<='Z';++c)
                {
                    int nj=go(j,c);
                    if(nj<3)dp[i+1][nj]=(dp[i+1][nj]+cur)%mod;
                }
            }
            else
            {
                int nj=go(j,s[i]);
                if(nj<3)dp[i+1][nj]=(dp[i+1][nj]+cur)%mod;
            }
        }
    }
    int avoid=0;
    for(int i=0;i<3;++i)avoid=(avoid+dp[n][i])%mod;
    int tot=qpow(26,q);
    cout<<(tot-avoid+mod)%mod<<'\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}