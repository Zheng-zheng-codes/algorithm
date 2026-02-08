//https://ac.nowcoder.com/acm/contest/120563/C
//有两种可能的结果：010101……    101010……
//分别统计这两种不同的结果对应的要调整的子序列
//统计前面可以参与配对的0和1的个数
//如果没有可以配对的就加总数，最终得到结果
#include<bits/stdc++.h>
using namespace std;
int ans(string&s)
{
    int ans=0;
    int sum0=0,sum1=0;
    int tmp=0;
    for(int i=0;i<s.size();++i)
    {
        if(s[i]=='0')sum0++;
        else sum1++;
        if(s[i]=='0'&&sum1==0)ans++;
        else if(s[i]=='1'&&sum0==0)ans++;
        else if(s[i]=='0'&&sum1!=0)sum1--;
        else sum0--;
    }
    return ans;
}
void solve()
{
    int n;cin>>n;
    string s;cin>>s;
    string t;
    for(int i=0;i<n;++i)
    {
        if(s[i]=='0'&&(i&1))t+='0';
        else if(s[i]=='1'&&!(i&1))t+='1';
    }
    int tmp=ans(t);
    t="";
    for(int i=0;i<n;++i)
    {
        if(s[i]=='0'&&!(i&1))t+='0';
        else if(s[i]=='1'&&(i&1))t+='1';
    }
    int tmp2=ans(t);
    cout<<min(tmp,tmp2)<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
} 