/*
题目描述
我们称一个正整数 x 是幸运数，当且仅当它的十进制表示中不包含数字串集合 s 中任意一个元素作为其子串。
例如当 s={22,333,0233} 时，233 是幸运数，2333、20233、3223 不是幸运数。给定 n 和 s，计算不大于 n 的幸运数个数。
答案对 10^9+7 取模。
输入格式
第一行有一个整数，表示 n。
第二行有一个整数，表示 s 中的元素个数 m。
接下来 m 行，每行一个数字串 si，表示 s 中的一个元素。
输出格式
输出一行一个整数，表示答案对 10^9+7 取模的结果。
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int maxn=1300;//文章的最大字符数
const int maxm=2000;//最大节点数
int cnt=0;
int tree[maxm][10];//字典树
int fail[maxm];//fail指针
int alert[maxm];//节点的警报
int dp[maxn][maxm][2][2];//记忆化搜索（数位dp）
string n;//文章
void insert(int i,string&s)//字典树插入字符串
{
    int u=0;
    for(int j=0;j<s.size();j++)
    {
        int c=s[j]-'0';
        if(tree[u][c]==0)tree[u][c]=++cnt;
        u=tree[u][c];
    }
    alert[u]=1;
}
void setfail()//设置fail指针和直通表
{
    fail[0]=0;
    queue<int>q;//类似bfs
    for(int i=0;i<10;i++)
    {
        if(tree[0][i])q.push(tree[0][i]);
    }
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        for(int i=0;i<10;i++)
        {
            if(tree[tmp][i])
            {
                fail[tree[tmp][i]]=tree[fail[tmp]][i];
                //该点的fail指针直接更新为父节点的fail指针直通的位置
                q.push(tree[tmp][i]);
            }
            else tree[tmp][i]=tree[fail[tmp]][i];
            //把tree变成一个直通表(优化绕圈)
            //如果没法直接到达，就更新为fail指针能直接到达的位置
        }
        alert[tmp]|=alert[fail[tmp]];
    }
}
//文章来到i
//当前位于字典树j节点
//free：能不能在0~9中随便选
//has：前面有没有数
int f(int i,int j,int free,int has)
{
    if(alert[j])return 0;//遇见警报
    if(i==n.size())return has;//文章没了，直接返回有没有数即可
    if(dp[i][j][free][has]!=-1)return dp[i][j][free][has];
    int cur=n[i]-'0';
    int ans=0;
    if(has)//前面有数
    {
        if(free)//可以随便选
        {
            for(int t=0;t<=9;t++)
            {
                ans=(ans+f(i+1,tree[j][t],1,1))%mod;
            }
        }
        else//不可以随便选
        {
            for(int t=0;t<cur;t++)
            {
                ans=(ans+f(i+1,tree[j][t],1,1))%mod;
            }
            ans=(ans+f(i+1,tree[j][cur],0,1))%mod;
        }
    }
    else//前面没有数
    {
        ans=(ans+f(i+1,j,1,0))%mod;//继续不选数
        if(free)//可以随便选
        {
            for(int t=1;t<=9;t++)
            {
                ans=(ans+f(i+1,tree[j][t],1,1))%mod;
            }
        }
        else//不可以随便选
        {
            for(int t=1;t<cur;t++)
            {
                ans=(ans+f(i+1,tree[j][t],1,1))%mod;
            }
            ans=(ans+f(i+1,tree[j][cur],0,1))%mod;
        }
    }
    dp[i][j][free][has]=ans;
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    int m;cin>>m;
    for(int i=0;i<m;i++)
    {
        string str;
        cin>>str;
        insert(i,str);
    }
    setfail();
    memset(dp,-1,sizeof(dp));
    cout<<f(0,0,0,0);
    return 0;
}