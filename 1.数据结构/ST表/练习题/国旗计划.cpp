//https://www.luogu.com.cn/problem/P4155
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
struct line
{
    int l,r,idx;
}lines[maxn<<1];
int st[maxn<<1][20];//st[i][j]:从i号线段开始走2^j步能到达的最远位置
int ans[maxn];
static bool cmp(line a,line b)
{
    return a.l<b.l;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>lines[i].l>>lines[i].r;
        if(lines[i].r<lines[i].l)lines[i].r+=m;
        lines[i].idx=i;
    }
    sort(lines+1,lines+1+n,cmp);
    for(int i=1;i<=n;++i)
    {
        lines[i+n].idx=lines[i].idx;
        lines[i+n].l=lines[i].l+m;
        lines[i+n].r=lines[i].r+m;
    }
    int e=n<<1;
    for(int i=1,arrive=1;i<=e;++i)
    {
        while(lines[arrive+1].l<=lines[i].r&&arrive+1<=e)arrive++;
        st[i][0]=arrive;
    }
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i<=e;++i)st[i][p]=st[st[i][p-1]][p-1];
    }
    for(int i=1;i<=n;++i)
    {
        int aim=lines[i].l+m;
        int cur=i;
        int res=0;
        for(int p=power;p>=0;--p)
        {
            if(st[cur][p]!=0&&lines[st[cur][p]].r<aim)
            {
                res+=(1<<p);
                cur=st[cur][p];
            }
        }
        ans[lines[i].idx]=res+2;
    }
    for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
}