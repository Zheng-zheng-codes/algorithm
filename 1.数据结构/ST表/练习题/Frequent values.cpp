//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2176
//把一样的数字建立成一个桶，对每个桶元素的个数建立ST表
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
struct bucket
{
    int l;
    int r;
}buc[maxn];
int where[maxn];
int st[maxn][17];
int cnt=1;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,q;
    while(cin>>n)
    {
        if(n==0)break;
        cin>>q;
        cnt=1;
        for(int i=1;i<=n;++i)cin>>a[i];
        buc[1].l=1;
        where[1]=1;
        for(int i=2;i<=n;++i)
        {
            if(a[i]!=a[i-1])
            {
                buc[cnt++].r=i-1;
                buc[cnt].l=i;
            }
            where[i]=cnt;
        }
        buc[cnt].r=n;
        for(int i=1;i<=cnt;++i)st[i][0]=buc[i].r-buc[i].l+1;
        int power=(int)log2(cnt);
        for(int p=1;p<=power;++p)
        {
            for(int i=1;i+(1<<p)-1<=cnt;++i)
            {
                int tmp=1<<(p-1);
                st[i][p]=max(st[i][p-1],st[i+tmp][p-1]);
            }
        }
        while(q--)
        {
            int l,r;cin>>l>>r;
            int lb=where[l],rb=where[r];
            if(lb==rb)
            {
                cout<<r-l+1<<'\n';
                continue;
            }
            int num1=buc[lb].r-l+1,num2=r-buc[rb].l+1;
            if(rb==lb+1)
            {
                cout<<max(num1,num2)<<'\n';
                continue;
            }
            int tmp=(int)log2((rb-1)-(lb+1)+1);
            int num3=0;
            if(lb+1<=rb-1)num3=max(st[lb+1][tmp],st[rb-1-(1<<tmp)+1][tmp]);
            cout<<max(max(num1,num2),num3)<<'\n';
        }
    }
}