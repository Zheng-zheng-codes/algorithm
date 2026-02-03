//https://www.luogu.com.cn/problem/P3379
//先将两个节点中较低的提高到同一层，再进行倍增
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
vector<int>tu[maxn];
int deep[maxn];
int st[maxn][19];
void dfs(int n)
{
    for(int i=0;i<tu[n].size();++i)
    {
        int tmp=tu[n][i];
        if(!deep[tmp])
        {
            deep[tmp]=deep[n]+1;
            st[tmp][0]=n;
            dfs(tmp);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m,s;cin>>n>>m>>s;
    for(int i=0;i<n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    memset(st,-1,sizeof(st));
    deep[s]=1;
    dfs(s);
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i<=n;++i)
        {
            if(st[i][p-1]!=-1)st[i][p]=st[st[i][p-1]][p-1];
        }
    }
    while(m--)
    {
        int a,b;cin>>a>>b;
        if(deep[a]<deep[b])swap(a,b);
        int tmp=deep[a]-deep[b];
        int power2=(int)log2(tmp);
        for(int p=power2;p>=0;--p)
        {
            if(tmp>=(1<<p))
            {
                tmp-=(1<<p);
                a=st[a][p];
            }
        }
        if(a==b)
        {
            cout<<a<<'\n';
            continue;
        }
        int power3=(int)log2(deep[a]);
        for(int p=power3;p>=0;--p)
        {
            if(st[a][p]!=st[b][p])
            {
                a=st[a][p];
                b=st[b][p];
            }
        }
        cout<<st[a][0]<<'\n';
    }
}