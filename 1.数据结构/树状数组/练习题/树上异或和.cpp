/*
题目描述
给一棵含有 n 个结点的有根树，根结点为 1 ，每个点有点权。现在有两种操作，格式如下：
1 x y：该操作表示将点 x 的点权改为 y。
2 x：该操作表示查询以结点 x 为根的子树内的所有点的点权的异或和。
现有长度为 m 的操作序列，请对于每个第二类操作给出正确的结果。
输入描述
输入的第一行包含两个正整数 n, m 用一个空格分隔。第二行包含 n 个整数为 n 个点的点权，相邻整数之间使用一个空格分隔。
接下来 n−1 行，每行包含两个正整数，表示一条边。
接下来 m 行，每行包含一个操作。
格式为：
1 x y
2 x
含义如上解释
输出描述
对于每一个类型为 2 的操作，输出结果
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int node[maxn];
int tin[maxn];//每个节点开始访问的时间戳
int tout[maxn];//每个节点所在子树结束访问的时间戳
int tree[maxn];//存储按照dfs的顺序排序后的异或和
vector<int>tu[maxn];
bool jud[maxn];
int cnt;
void dfs(int i)
{
    jud[i]=1;
    tin[i]=++cnt;
    for(int j=0;j<tu[i].size();++j)
    {
        if(jud[tu[i][j]])continue;
        dfs(tu[i][j]);
    }
    tout[i]=cnt;
}
void add(int pos,int num)
{
    while(pos<=cnt)
    {
        tree[pos]^=num;
        pos+=pos&(-pos);
    }
}
int query(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans^=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>node[i];
    for(int i=1;i<=n-1;++i)
    {
        int a,b;cin>>a>>b;
        tu[a].push_back(b);
        tu[b].push_back(a);
    }
    dfs(1);
    for(int i=1;i<=n;++i)add(tin[i],node[i]);
    while(m--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x,y;cin>>x>>y;
            int num=node[x]^y;
            add(tin[x],num);
            node[x]=y;
        }
        else
        {
            int x;cin>>x;
            cout<<(query(tout[x])^query(tin[x]-1))<<'\n';
        }
    }
}