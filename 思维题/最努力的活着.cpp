/*
小 E 在仿照约瑟夫问题进行模拟游戏，游戏规则是这样的：
有n 个人排成一排，每个人都有一个价值。游戏初始有一个参数 1≤w≤n。
n 个人的位置下标从1 开始算，即 1,2,?,n。
每一轮，首先统计当前在场的所有人的价值和，计入 sum。
再查看当前剩余人数，如果 <w，游戏结束。
如果游戏没有结束，淘汰所有位置下标是 
w 的倍数的人，人的下标从 1 开始编号，所有淘汰结束后，未被淘汰的人按照从左到右重新编号。并重新开始新的一轮。
小 E 的目标是最大化最终得到的 sum，而 ta 唯一能决定的是初始每个人的价值。
已知这n 个人的价值序列恰好是 1,2,…,n 的排列，位置可以任意安排，求能得到的最大 sum。
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
using i128 = __int128;
void print_i128(i128 x) 
{
    if (x == 0) { putchar('0'); return; }
    if (x < 0) { putchar('-'); x = -x; }
    char buf[64]; int p = 0;
    while (x > 0) 
    {
        int digit = (int)(x % 10);
        buf[p++] = '0' + digit;
        x /= 10;
    }
    while (p--) putchar(buf[p]);
}
void solve() 
{
    int n,w;
    cin>>n>>w;
    i128 sum=(i128)n*(n + 1)/2;//总和
    int R=0;//目前取到的最右侧的值
    i128 ans=0;
    while(1) 
	{
        int num=n-R;//右侧有num个数没有分配
        if (num<w)//剩余的数小于w直接加上剩余的值 
		{
            ans+=sum-(i128)R*(R+1)/2;
            break;
        }
        int a=num/w;//当前能去掉的个数
        //1.为什么能删除k次
        int k=(n-R-w*a)/a+w/a;//能去掉k次a个
        //2.删除k次的和是怎么算的
        i128 sum0=sum-(i128)R*(R+1)/2;//右半部分的数字和
        i128 now=(i128)R+1;//当前来到的值
        i128 C=(i128)a*now+(i128)a*(a-1)/2;
        i128 D=(i128)a*a;
        i128 K=(i128)k;
        i128 tot=K*sum0-(C*(K*(K-1)/2)+D*(K*(K-1)*(K-2)/6));
        ans+=tot;
        R+=k*a;//更新删除后的右边界
    }
    print_i128(ans);
    putchar('\n');
}
signed main() 
{
    int t;cin>>t;
    while(t--)solve();
    return 0;
}