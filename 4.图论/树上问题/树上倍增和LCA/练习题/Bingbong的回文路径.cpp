//https://ac.nowcoder.com/acm/contest/78807/G
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
const int base=499;
vector<int>tu[maxn];
int a[maxn];
int deep[maxn];
int st[maxn][17];
int st2[maxn][17];//记录往上跳跃的哈希值
int st3[maxn][17];//记录从某一祖先节点往下跳跃到当前节点的哈希值
bool jud[maxn];
int qpow[maxn];
int power;
string s;
void dfs(int n)
{
    jud[n]=1;
    for(int i=0;i<tu[n].size();++i)
    {
        int j=tu[n][i];
        if(jud[j])continue;
        deep[j]=deep[n]+1;
        st[j][0]=n;
        st2[j][0]=s[n]-'a'+1;
        st3[j][0]=s[n]-'a'+1;
        dfs(j);
    }
}
int lca(int a,int b)
{
    if(deep[a]<deep[b])swap(a,b);
    if(deep[a]!=deep[b])
    {
        int tmp=deep[a]-deep[b];
        for(int p=power;p>=0;--p)
        {
            if(tmp>=(1<<p))
            {
                tmp-=(1<<p);
                a=st[a][p];
            }
        }
    }
    if(a==b)return a;
    for(int p=power;p>=0;--p)
    {
        if(st[a][p]!=st[b][p]&&st[a][p]!=-1)
        {
            a=st[a][p];
            b=st[b][p];
        }
    }
    return st[a][0];
}
//通过计算两个哈希值判断两个字符串是否相等
int has(int x,int mid,int y)
{
    int now=s[x]-'a'+1;
    int idx=x;
    for(int p=power;p>=0;--p)
    {
        if(st[idx][p]!=-1&&deep[st[idx][p]]>=deep[mid])
        {
            now=now*qpow[1<<p]+st2[idx][p];
            idx=st[idx][p];
        }
    }
    int on=now;
    if(y==mid)return on;
    now=s[y]-'a'+1;
    int height=1;
    idx=y;
    for(int p=power;p>=0;--p)
    {
        if(st[idx][p]!=-1&&deep[st[idx][p]]>deep[mid])
        {
            now=st3[idx][p]*qpow[height]+now;
            idx=st[idx][p];
            height+=(1<<p);
        }
    }
    int down=now;
    return on*qpow[height]+down;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(st,-1,sizeof(st));
    int n;cin>>n;
    power=(int)log2(n);
    qpow[0]=1;
    for(int i=1;i<=n;++i)qpow[i]=qpow[i-1]*base;
    cin>>s;
    s=' '+s;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        tu[a[i]].push_back(i);
        tu[i].push_back(a[i]);
    }
    deep[1]=0;
    dfs(1);
    for(int p=1;p<=power;++p)
    {
        for(int i=1;i<=n;++i)
        {
            if(st[i][p-1]!=-1)
            {
                st[i][p]=st[st[i][p-1]][p-1];
                st2[i][p]=st2[i][p-1]*qpow[1<<(p-1)]+st2[st[i][p-1]][p-1];
                st3[i][p]=st3[st[i][p-1]][p-1]*qpow[1<<(p-1)]+st3[i][p-1];
            }
        }
    }
    int q;cin>>q;
    while(q--)
    {
        int x,y;cin>>x>>y;
        int mid=lca(x,y);
        if(has(x,mid,y)==has(y,mid,x))cout<<"YES\n";
        else cout<<"NO\n";
    }
}