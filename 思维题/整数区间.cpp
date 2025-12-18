/*
题目描述
请编程完成以下任务：
1.从文件中读取闭区间的个数及它们的描述；
2.找到一个含元素个数最少的集合,使得对于每一个区间,都至少有一个整数属于该集合，输出该集合的元素个数。
输入描述
首行包括区间的数目n,1≤n≤10000,接下来的n行,每行包括两个整数a,b,
被一空格隔开,0≤a≤b≤10000,它们是某一个区间的开始值和结束值。
输出描述
第一行集合元素的个数,对于每一个区间都至少有一个整数属于该区间,且集合所包含元素数目最少。
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct line
{
    int s,e;
};
static bool cmp(line a,line b)
{
    return a.e<b.e;
}
signed main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    vector<line>l(n);
    for(int i=0;i<n;++i)cin>>l[i].s>>l[i].e;
    sort(l.begin(),l.end(),cmp);
    int num=0,fin=-1;
    for(int i=0;i<n;++i)
    {
        if(l[i].s>fin)num++,fin=l[i].e;
    }
    cout<<num;
}
