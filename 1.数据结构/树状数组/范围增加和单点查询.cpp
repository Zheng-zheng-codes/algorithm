//https://www.luogu.com.cn/problem/P3368
//用树状数组维护差分数组的信息即可
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
        int num;cin>>num;
        add(i,num,n);
        add(i+1,-num,n);
    }
    while(m--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x,y,k;cin>>x>>y>>k;
            add(x,k,n);
            add(y+1,-k,n);
        }
        else
        {
            int x;cin>>x;
            cout<<sum(x)<<'\n';
        }
    }
}