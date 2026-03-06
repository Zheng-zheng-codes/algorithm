//https://codeforces.com/gym/105537/problem/K
//实现不了的字符串一定是只有一个字母的
#include<bits/stdc++.h>
using namespace std;
int cnt[26];
bool jud[26];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,e;cin>>n>>e;
    for(int i=0;i<n;++i)
    {
        string s;cin>>s;
        char c=s[0];
        cnt[c-'a']++;
        if(s.size()==1)jud[c-'a']=1;
        for(int j=1;j<s.size();++j)
        {
            if(s[j]==c)
            {
                cnt[c-'a']++;
                if(j==s.size()-1)jud[c-'a']=1;
            }
            else break;
        }
    }
    bool tmp=0;
    for(int i=0;i<e;++i)
    {
        if(!jud[i])
        {
            tmp=1;
            break;
        }
    }
    if(!tmp)cout<<"NO";
    else
    {
        char c='.';
        int ans=INT_MAX;
        for(int i=0;i<e;++i)
        {
            if(jud[i])continue;
            if(cnt[i]<ans)
            {
                ans=cnt[i];
                c='a'+i;
            }
        }
        ans++;
        while(ans--)cout<<c;
    }
}