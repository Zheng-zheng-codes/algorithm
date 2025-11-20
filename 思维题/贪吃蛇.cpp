//https://www.luogu.com.cn/problem/P7078
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
//对于最强的蛇：如果它吃掉最弱的蛇以后不是最弱的就吃，否则不吃
//如果吃完了还是最强的，不吃白不吃
//吃完了以后不是最强大，这时最强的没有原来强，最弱的没有原来弱
//当前最强蛇吃完后会死在原来最强蛇前面
//吃完了如果变成最弱蛇了，新的最强蛇会可能会吃掉它
//接下来第二强的蛇以此类推
const int maxn=1e6+10;
int snake[maxn];
int n;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t=1;cin>>t;
    for(int i=1;i<=t;i++)
    {
        if(i==1)
        {
            cin>>n;
            for(int j=1;j<=n;j++)cin>>snake[j];
        }
        else
        {
            int k;cin>>k;
            while(k--)
            {
                int x,y;cin>>x>>y;
                snake[x]=y;
            }
        }
        deque<pii>dq1,dq2;
        for(int j=1;j<=n;j++)dq1.emplace_back(snake[j],j);
        int ans;
        while(1)
        {
            if(dq1.size()+dq2.size()==2)
            {
                ans=1;
                break;
            }
            pii strong,weak;
            weak=dq1.front();
            dq1.pop_front();
            if(dq2.empty()||!dq1.empty()&&dq1.back()>dq2.back())
            {
                strong=dq1.back();
                dq1.pop_back();
            }
            else
            {
                strong=dq2.back();
                dq2.pop_back();
            }
            pii now;
            now.first=strong.first-weak.first;
            now.second=strong.second;
            if(dq1.empty()||dq1.front()>now)//不能吃
            {
                ans=dq1.size()+dq2.size()+2;
                int cnt=0;
                while(1)
                {
                    cnt++;
                    if(dq1.size()+dq2.size()+1==2)
                    {
                        if(cnt%2==0)ans--;
                        break;
                    }
                    pii tmp;
                    if(dq2.empty()||!dq1.empty()&&dq1.back()>dq2.back())
                    {
                        tmp=dq1.back();
                        dq1.pop_back();
                    }
                    else
                    {
                        tmp=dq2.back();
                        dq2.pop_back();
                    }
                    pii tmp2;
                    tmp2.first=tmp.first-now.first;
                    tmp2.second=tmp.second;
                    now=tmp2;
                    if((dq1.empty()||now<dq1.front())&&(dq2.empty()||now<dq2.front()))continue;
                    else
                    {
                        if(cnt%2==0)ans--;
                        break;
                    }
                }
                break;
            }
            else dq2.push_front(now);
        }
        cout<<ans<<'\n';
    }
}