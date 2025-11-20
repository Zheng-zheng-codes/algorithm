//给定整数 n ，返回 所有小于非负整数?n?的质数的数量。
#include<bits/stdc++.h>
using namespace std;
int countPrimes(int n) 
{
    n--;
    if(n<=1)return 0;
    int cnt=(n+1)/2;//预估质数个数（已经删除了所有偶数）
    vector<bool>visited(n+1,0);
    //visited[i]=false：i是质数
    //visited[i]=true：i是合数
    for(int i=3;i*i<=n;i+=2)//只筛奇数即可
    {
        if(visited[i])continue;
        for(int j=i*i;j<=n;j+=2*i)
        {
            if(!visited[j])
            {
                visited[j]=1;
                cnt--;
            }
        }
    }
    return cnt;
}