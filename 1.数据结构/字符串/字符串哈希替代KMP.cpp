/*
给你两个字符串?haystack 和 needle，
请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。
如果?needle 不是 haystack 的一部分，则返回? -1 。
*/
#include<bits/stdc++.h>
using namespace std;
using ll=unsigned long long;
int base=499;
const int maxn=1e4+10;
ll bpow[maxn];//bpow[i]:base^i
ll ha[maxn];//ha[i]:前i位的哈希值
void init(string &s)//初始化
{
    bpow[0]=1;
    for(int i=1;i<s.size();i++)bpow[i]=bpow[i-1]*base;
    ha[0]=s[0]-'a'+1;
    for(int i=1;i<s.size();i++)ha[i]=ha[i-1]*base+s[i]-'a'+1;
} 
ll has(int lef,int rig)//得到从lef到rig子串的哈希值
{
    if(lef==0)return ha[rig];
    else return ha[rig]-ha[lef-1]*bpow[rig-lef+1];
}
int strStr(string haystack, string needle) 
{
    init(haystack);   
    int n=needle.size();
    ll num=needle[0]-'a'+1;
    for(int i=1;i<n;i++)num=num*base+needle[i]-'a'+1;
    for(int i=0,j=n-1;j<haystack.size();i++,j++)
    {
        if(has(i,j)==num)return i;
    }
    return -1;
}