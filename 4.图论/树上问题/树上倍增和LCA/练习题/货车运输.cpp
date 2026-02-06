//https://www.luogu.com.cn/problem/P1967
//为了减少束缚所以要用最少的边，而且边权要最大，但是要保证最大的连通-->最大生成树
//在最大生成树中找最近公共祖先，最小边权即为答案
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e4+10;
const int maxm=5e4+10;
const int maxv=1e5+10;
vector<pii>tu[maxn];
struct edges
{
    int x,y,z;
}e[maxm];
static bool cmp(edges e1,edges e2)
{
    return e1.z>e2.z;
}
int fa[maxn];
void init(int n)
{
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
    }
}
int find(int n)
{
    if(n!=fa[n])
    {
        fa[n]=find(fa[n]);
    }
    return fa[n];
}
void unit(int x,int y)
{
    int fx=find(x),fy=find(y);
    fa[fx]=fy;
}
int deep[maxn];
bool jud[maxn];
int st[maxn][14];
int st2[maxn][14];
void dfs(int n)
{
    jud[n]=1;
    for(int i=0;i<tu[n].size();++i)
    {
        int tmp=tu[n][i].first;
        if(jud[tmp])continue;
        st[tmp][0]=n;
        st2[tmp][0]=tu[n][i].second;
        deep[tmp]=deep[n]+1;
        dfs(tmp);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;++i)cin>>e[i].x>>e[i].y>>e[i].z;
    init(n);
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;++i)
    {
        int fx=find(e[i].x);
        int fy=find(e[i].y);
        if(fx==fy)continue;
        else 
        {
            unit(fx,fy);
            tu[e[i].x].push_back({e[i].y,e[i].z});
            tu[e[i].y].push_back({e[i].x,e[i].z});
        }
    }
    memset(st,-1,sizeof(st));
    memset(st2,maxv,sizeof(st2));
    for(int i=1;i<=n;++i)
    {
        if(!jud[i])
        {
            deep[i]=1;
            dfs(i);
        }
    }
    int power=(int)log2(n);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i<=n;++i)
        {
            if(st[i][p-1]!=-1)
            {
                st[i][p]=st[st[i][p-1]][p-1];
                st2[i][p]=min(st2[i][p-1],st2[st[i][p-1]][p-1]);
            }
        }
    }
    int q;cin>>q;
    while(q--)
    {
        int x,y;cin>>x>>y;
        int fx=find(x),fy=find(y);
        if(fx!=fy)cout<<-1<<'\n';
        else
        {
            int ans=maxv;
            if(deep[x]<deep[y])swap(x,y);
            int tmp=deep[x]-deep[y];
            int power2=(int)log2(tmp);
            for(int p=power2;p>=0;--p)
            {
                if(tmp>=(1<<p))
                {
                    tmp-=1<<p;
                    if(st2[x][p]!=-1)
                    {
                        ans=min(ans,st2[x][p]);
                        x=st[x][p];
                    }
                }
            }
            if(x==y)
            {
                cout<<ans<<'\n';
                continue;
            }
            int nx=x,ny=y;
            tmp=deep[nx];
            int power3=(int)log2(tmp);
            for(int p=power3;p>=0;--p)
            {
                if(st[nx][p]!=st[ny][p])
                {
                    ans=min(ans,min(st2[nx][p],st2[ny][p]));
                    nx=st[nx][p];
                    ny=st[ny][p];
                }
            }
            ans=min(ans,min(st2[nx][0],st2[ny][0]));
            cout<<ans<<'\n';
        }
    }
}