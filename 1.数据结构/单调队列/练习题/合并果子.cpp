//https://ac.nowcoder.com/acm/contest/120565/D
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
const int maxm=1e6+10;
const int mod=1e9+7;
int cnt[maxm];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=0;i<n;++i)
    {
        int c,w;cin>>c>>w;
        cnt[w]+=c;
    }
    queue<pii>q1;
    queue<pii>q2;
    for(int i=1;i<=1000000;++i)
    {
        if(cnt[i])q1.push({i,cnt[i]});
    }
    int ans=0;
    while(1)
    {
        if(q1.size()+q2.size()==1)
        {
            int a=0;
            if(!q1.empty())a+=q1.front().second;
            if(!q2.empty())a+=q2.front().second;
            if(a==1)break;
        }
        int x,y;
        if(q2.empty()||(!q1.empty()&&q1.front().first<q2.front().first))
        {
            int tmp=q1.front().first;
            int num=q1.front().second;
            if(num>1)
            {
                int val=tmp*2%mod;
                q2.push({val,num/2});
                ans=(ans+(val*(num/2))%mod)%mod;
            }
            q1.front().second%=2;
            if(q1.front().second==0)
            {
                q1.pop();
                continue;
            }
            else 
            {
                x=q1.front().first;
                q1.pop();
            }
        }
        else
        {
            int tmp=q2.front().first;
            int num=q2.front().second;
            if(num>1)
            {
                int val=tmp*2%mod;
                q2.push({val,num/2});
                ans=(ans+(val*(num/2))%mod)%mod;
            }
            q2.front().second%=2;
            if(q2.front().second==0)
            {
                q2.pop();
                continue;
            }
            else 
            {
                x=q2.front().first;
                q2.pop();
            }
        }
        if(q2.empty()||(!q1.empty()&&q1.front().first<q2.front().first))
        {
            y=q1.front().first;
            q1.front().second--;
            if(q1.front().second==0)q1.pop();
        }
        else
        {
            y=q2.front().first;
            q2.front().second--;
            if(q2.front().second==0)q2.pop();
        }
        int tmp=(x+y)%mod;
        if(!q2.empty()&&q2.back().first==tmp)q2.back().second++;
        else q2.push({tmp,1});
        ans=(ans+tmp)%mod;
    }
    cout<<ans;  
}