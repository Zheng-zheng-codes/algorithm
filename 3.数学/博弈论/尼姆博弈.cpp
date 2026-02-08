//https://www.luogu.com.cn/problem/P2197
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)
    {
        int n;cin>>n;
        int ans=0;
        while(n--)
        {
            int num;cin>>num;
            ans^=num;
        }
        if(ans==0)cout<<"No\n";
        else cout<<"Yes\n";
    }
}