//https://leetcode.cn/problems/maximize-value-of-function-in-a-ball-passing-game/description/
#include<bits/stdc++.h>
using namespace std;
static const int maxn=1e5+10;
int st[maxn][34];//st[i][p]：i经过2^p次能到达的位置
long long st2[maxn][34];//st[i][p]：i经过2^p次贡献的函数值
int m;
int power;
int where[34];
void build(long long k)//把k的所有二进制位都提前存储下来
{
    power=(int)log2(k);
    for(int p=power;p>=0;--p)
    {
        if(k>=(1LL<<p))
        {
            k-=(1LL<<p);
            where[m++]=p;
        }
    }
}
long long getMaxFunctionValue(vector<int>& receiver, long long k) 
{
    build(k);
    int n=receiver.size();
    for(int i=0;i<n;++i)
    {
        st[i][0]=receiver[i];
        st2[i][0]=receiver[i];
    }
    for(int p=1;p<=power;++p)
    {
        for(int i=0;i<n;++i)
        {
            st[i][p]=st[st[i][p-1]][p-1];
            st2[i][p]=st2[i][p-1]+st2[st[i][p-1]][p-1];
        }
    }
    long long ans=0;
    for(int i=0;i<n;++i)
    {
        long long sum=i;
        long long tmp=k;
        int now=i;
        for(int j=0;j<m;++j)
        {
            sum+=st2[now][where[j]];
            now=st[now][where[j]];
        }
        ans=max(sum,ans);
    }
    return ans;
}