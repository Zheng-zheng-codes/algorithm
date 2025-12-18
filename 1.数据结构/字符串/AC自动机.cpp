#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;//目标串的最大数量
const int maxs=2e5+10;//最大总结点数
int en[maxn];//记录每个目标串结尾的编号
int times[maxs];//统计词频
int tree[maxs][26];//字典树
int fail[maxs];//fail指针
int cnt=0;//前缀树节点编号
vector<int>tu[maxs];//建图优化统计时的复杂度
void insert(int i,string&s)//字典树插入字符串
{
    int u=0;
    for(int j=0;j<s.size();j++)
    {
        int c=s[j]-'a';
        if(tree[u][c]==0)tree[u][c]=++cnt;
        u=tree[u][c];
    }
    en[i]=u;
}
void setfail()//设置fail指针和直通表
{
    fail[0]=0;
    queue<int>q;//类似bfs
    for(int i=0;i<26;i++)
    {
        if(tree[0][i])q.push(tree[0][i]);
    }
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(tree[tmp][i])
            {
                fail[tree[tmp][i]]=tree[fail[tmp]][i];
                //该点的fail指针直接更新为父节点的fail指针直通的位置
                q.push(tree[tmp][i]);
            }
            else tree[tmp][i]=tree[fail[tmp]][i];
            //把tree变成一个直通表(优化绕圈)
            //如果没法直接到达，就更新为fail指针能直接到达的位置
        }
    }
}
void dfs(int u) 
{
    for (int v:tu[u]) 
    {
        dfs(v);               // 先算子节点
        times[u]+=times[v]; // 再加到父节点
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;
        insert(i,str);
    }
    setfail();
    string word;
    cin>>word;
    int u=0;
    for(int i=0;i<word.size();i++)
    {
        u=tree[u][word[i]-'a'];
        times[u]++;//统计每个位置的词频
    }
    for(int i=1;i<=cnt;i++)tu[fail[i]].push_back(i);
    dfs(0);
    for(int i=0;i<n;i++)
    {
        cout<<times[en[i]]<<'\n';
    }
    return 0;
}