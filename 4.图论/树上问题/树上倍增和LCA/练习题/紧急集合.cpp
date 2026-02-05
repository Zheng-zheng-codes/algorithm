//https://www.luogu.com.cn/problem/P4281
//树上的三个点a、b、c，两两配对的三个公共最近祖先，其实最多有两个
//一定有一个节点在另外两个节点和它们的最近公共祖先组成的子树中，
//显然一定会和其中一个点的公共最近祖先是另外两个点的最近公共祖先
//两个公共最近祖先中汇聚点即为较低的那个（如果高一点就会费两倍的距离）
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
vector<int>tu[maxn];
int deep[maxn];
int st[maxn][19];
bool jud[maxn];
void dfs(int n)
{
    jud[n]=1;
    for(int i=0;i<tu[n].size();++i)
    {
        int tmp=tu[n][i];
        if(jud[tmp])continue;
        deep[tmp]=deep[n]+1;
        st[tmp][0]=n;
        dfs(tmp);
    }
}
int lca(int a,int b)
{
    if(deep[a]<deep[b])swap(a,b);
    int tmp=deep[a]-deep[b];
    int power=(int)log2(tmp);
    for(int p=power;p>=0;--p)
    {
        if(tmp>=(1LL<<p))
        {
            tmp-=(1LL<<p);
            a=st[a][p];
        }
    }
    if(a==b)return a;
    int power2=(int)log2(deep[a]);
    for(int p=power2;p>=0;--p)
    {
        if(st[a][p]!=st[b][p]&&st[a][p]!=-1&&st[b][p]!=-1)
        {
            a=st[a][p];
            b=st[b][p];
        }
    }
    return st[a][0];
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=0;i<n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    deep[1]=1;
    memset(st,-1,sizeof(st));
    dfs(1);
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
        int a,b,c;cin>>a>>b>>c;
        int x=lca(a,b),y=lca(a,c),z=lca(b,c);
        int p,q;
        if(x==y)p=x,q=z;
        else if(y==z)p=y,q=x;
        else p=x,q=y;
        int high=deep[p]>deep[q]?q:p;
        int low=deep[p]>deep[q]?p:q;
        int money=deep[a]+deep[b]+deep[c]-deep[low]-deep[high]*2;
        cout<<low<<' '<<money<<'\n';
    }
}