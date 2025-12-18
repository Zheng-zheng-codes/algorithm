/*
题目描述
给定 n 个闭区间 \[a_i;b_i\]，其中i=1,2,...,n。任意两个相邻或相交的闭区间可以合并为一个闭区间。例如，\[1;2\] 和 \[2;3\] 可以合并为 \[1;3\]，\[1;3\] 和 \[2;4\] 可以合并为 \[1;4\]，但是\[1;2\] 和 \[3;4\] 不可以合并。
我们的任务是判断这些区间是否可以最终合并为一个闭区间，如果可以，将这个闭区间输出，否则输出no。
输入描述
第一行为一个整数n，3≤n≤50000。表示输入区间的数量。
之后n行，在第i行上（1≤i≤n），为两个整数 a_i 和 b_i ，整数之间用一个空格分隔，表示区间 \[a_i;b_i\]（其中 1≤a_i≤b_i≤10000）。
输出描述
输出一行，如果这些区间最终可以合并为一个闭区间，输出这个闭区间的左右边界，用单个空格隔开；否则输出 no。
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
    if(a.s!=b.s)return a.s<b.s;
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
    int num=0,lef=l[0].s,rig=l[0].e;
    for(int i=1;i<n;++i)
    {
        if(l[i].s>rig)
        {
            cout<<"no";
            return 0;
        }
        rig=max(rig,l[i].e);
    }
    cout<<lef<<' '<<rig;
}
