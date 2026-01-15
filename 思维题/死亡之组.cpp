//https://acm.hdu.edu.cn/showproblem.php?pid=7468
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)
    {
        int n,l,d;cin>>n>>l>>d;
        for(int i=1;i<=n;++i)cin>>a[i];
        if(a[1]>=l)
        {
            int num=0;
            for(int i=2;i<=n;++i)
            {
                if(a[i]<l)num++;
            }
            if(num<3)
            {
                cout<<"No"<<'\n';
                continue;
            }
            else
            {
                int tmp=l;
                for(int i=2;i<=n;++i)tmp=min(tmp,a[i]);
                if(a[1]-tmp<=d)
                {
                    cout<<"No"<<'\n';
                    continue;
                }
                else
                {
                    cout<<"Yes"<<'\n';
                    continue;
                }
            }
        }
        else
        {
            int tmp=0;
            for(int i=2;i<=n;++i)tmp=max(tmp,a[i]);
            if(tmp>=l)
            {
                int num=0;
                for(int i=1;i<=n;++i)
                {
                    if(a[i]<l)num++;
                }
                if(num<3)
                {
                    cout<<"No"<<'\n';
                    continue;
                }
                int minum=INT_MAX;
                for(int i=1;i<=n;++i)minum=min(minum,a[i]);
                if(tmp-minum>d)
                {
                    cout<<"Yes"<<'\n';
                    continue;
                }
                else
                {
                    cout<<"No"<<'\n';
                    continue;
                }
            }
            else
            {
                sort(a+2,a+n+1);
                int num1=max(a[1],a[4]);
                int num2=min(a[1],a[2]);
                if(num1-num2>d)
                {
                    cout<<"Yes"<<'\n';
                    continue;
                }
                else
                {
                    cout<<"No"<<'\n';
                    continue;
                }
            }
        }
    }
}