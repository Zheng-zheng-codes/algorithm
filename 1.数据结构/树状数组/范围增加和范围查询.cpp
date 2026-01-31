//https://www.luogu.com.cn/problem/P3372
//求0~k的和：
//a1+a2+…+ak=(d1)+(d1+d2)+…+(d1+d2+…+dk)=k*(d1+d2+…+dk)-Σ(i-1)*di
//所以用两个树状数组分别维护di和(i-1)*di即可
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
int tree1[maxn];
int tree2[maxn];
void add(int pos,int num,int n,int choose)
{
    if(choose==1)
    {
        while(pos<=n)
        {
            tree1[pos]+=num;
            pos+=pos&(-pos);
        }
    }
    else
    {
        while(pos<=n)
        {
            tree2[pos]+=num;
            pos+=pos&(-pos);
        }
    }
    
}
int sum(int pos,int choose)
{
    int ans=0;
    if(choose==1)
    {
        while(pos>0)
        {
            ans+=tree1[pos];
            pos-=pos&(-pos);
        }
        return ans;
    }
    else
    {
        while(pos>0)
        {
            ans+=tree2[pos];
            pos-=pos&(-pos);
        }
        return ans;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        int num;cin>>num;
        add(i,num,n,1);
        add(i+1,-num,n,1);
        add(i,(i-1)*num,n,2);
        add(i+1,-i*num,n,2);
    }
    while(m--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x,y,k;cin>>x>>y>>k;
            add(x,k,n,1);
            add(y+1,-k,n,1);
            add(x,(x-1)*k,n,2);
            add(y+1,-y*k,n,2);
        }
        else
        {
            int x,y;cin>>x>>y;
            cout<<(y*sum(y,1)-sum(y,2))-((x-1)*sum(x-1,1)-sum(x-1,2))<<'\n';
        }
    }
}