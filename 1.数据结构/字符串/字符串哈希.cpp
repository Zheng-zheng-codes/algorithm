/*
题目描述
如题，给定 N 个字符串（第 i 个字符串长度为 Mi，字符串内包含数字、大小写字母，大小写敏感），
请求出 N 个字符串中共有多少个不同的字符串。
友情提醒：如果真的想好好练习哈希的话，请自觉。
输入格式
第一行包含一个整数 N，为字符串的个数。
接下来 N 行每行包含一个字符串，为所提供的字符串。
输出格式
输出包含一行，包含一个整数，为不同的字符串个数。
*/
#include<bits/stdc++.h>
using namespace std;
int base=499;
int tran(char c)
{
    if(c>='0'&&c<='9')return c-'0'+1;
    else if(c>='A'&&c<='Z')return c-'A'+11;
    else return c-'a'+37;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    vector<long long>v;
    while(n--)
    {
        string s;
        cin>>s;
        int ans=1;
        for(int i=0;i<s.size();i++)ans=ans*base+tran(s[i]);
        v.push_back(ans);
    }
    sort(v.begin(),v.end());
    int cnt=unique(v.begin(),v.end())-v.begin();
    cout<<cnt;
    return 0;
}