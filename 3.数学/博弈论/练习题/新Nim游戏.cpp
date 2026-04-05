//https://www.luogu.com.cn/problem/P4301
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=101;
int a[maxn];
int d[31];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    sort(a+1,a+1+n);
    int ans=0;
    for(int i=n;i>0;--i)
    {
        int x=a[i];
		for(int j=30;j>=0;--j)
        {
            if((x>>j)&1)
            {
                if(d[j])x^=d[j];
				else
                {
                    d[j]=x;
                    break;
                }
            }
				
        }
		if(!x)ans+=a[i];
	}
    cout<<ans;
}