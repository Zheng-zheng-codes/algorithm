//https://www.luogu.com.cn/problem/P4279
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
        bool jud=0;
        for(int i=0;i<n;i++)
        {
            int num;cin>>num;
            ans^=num;
            if(num!=1)jud=1;
        }
        if(!jud)
        {
            if(n&1)cout<<"Brother"<<'\n';
            else cout<<"John"<<'\n';
            continue;
        }
        if(ans==0)cout<<"Brother"<<'\n';
        else cout<<"John"<<'\n';
    }
}