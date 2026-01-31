//https://www.luogu.com.cn/problem/P3374
//树状数组的下标一定从1开始
//树状数组每个下标管的范围：二进制最右侧的1去掉再加1到它自己的范围
//例：12（1100）：9（1001）~12（1100）
//单点增加：不断加最右侧的1来达到所有管它的范围
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int tree[maxn];
void add(int pos,int num,int n)
{
    while(pos<=n)
    {
        tree[pos]+=num;
        pos+=pos&(-pos);
    }
}
int sum(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        int a;cin>>a;
        add(i,a,n);
    }
    while(m--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x,k;cin>>x>>k;
            add(x,k,n);
        }
        else
        {
            int l,r;cin>>l>>r;
            cout<<sum(r)-sum(l-1)<<'\n';
        }
    }
}