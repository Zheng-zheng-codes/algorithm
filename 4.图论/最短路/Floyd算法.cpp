/*
题目描述
农夫约翰正驾驶一条小艇在牛勒比海上航行。
海上有 N(1≤N≤100) 个岛屿，用1到N编号。约翰从1号小岛出发，最后到达N号小岛。
一张藏宝图上说，如果他的路程上经过的小岛依次出现了A1,A2,…,AM(2≤M≤10000) 这样的序列（不一定相邻），
那他最终就能找到古老的宝藏。但是，由于加勒比海有海盗出没，约翰知道任意两个岛屿之间的航线上海盗出没的概率，
他用一个危险指数 Di,j(0≤D i,j≤100000) 来描述。他希望他的寻宝活动经过的航线危险指数之和最小。
那么，在找到宝藏的前提下，这个最小的危险指数是多少呢？
输入格式
第一行：两个用空格隔开的正整数 N 和 M。
第二到第 M+1 行：第 i+1 行用一个整数Ai表示 FJ 必须经过的第 i个岛屿。保证 A1=1,AM=N。
第 M+2 到第 N+M+1 行：第 i+M+1 行包含 N 个用空格隔开的非负整数分别表示 
i号小岛到第 1…N 号小岛的航线各自的危险指数。保证第 i 个数是 0。
输出格式
第一行：FJ 在找到宝藏的前提下经过的航线的危险指数之和的最小值。
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<int>arr(m);
    for(int i=0;i<m;i++)cin>>arr[i];
    vector<vector<int>>tu(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>tu[i][j];
        }
    }
    for(int board=1;board<=n;board++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                tu[i][j]=min(tu[i][j],tu[i][board]+tu[board][j]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<m-1;i++)
    {
        ans+=tu[arr[i]][arr[i+1]];
    }
    cout<<ans;
    return 0;
}