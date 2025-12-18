#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;// 最大节点数
int tree[maxn][26];// 字典树，每个节点有 26 个字母（a-z）
int pass[maxn];// 记录到达每个节点的字符串数量
int e[maxn];// 记录以每个节点为结尾的字符串数量
int cnt;// 记录当前树的节点编号
void build()
{
    cnt=1;// 初始化节点计数器为 1
    //大于cnt的下标视为还没有用
}
void insert(string word)
{
    int cur=1;
    pass[cur]++;
    for(int i=0;i<word.size();i++)
    {
        int path=word[i]-'a';
        if(tree[cur][path]==0)tree[cur][path]=++cnt;//遇见空节点默认为使用cnt+1空间
        cur=tree[cur][path];
        pass[cur]++;
    }
    e[cur]++;
}
int search(string word)
{
    int cur=1;
    for(int i=0;i<word.size();i++)
    {
        int path=word[i]-'a';
        if(tree[cur][path]==0)return 0;
        cur=tree[cur][path];
    }
    return e[cur];
}
int start(string s)
{
    int cur=1;
    for(int i=0;i<s.size();i++)
    {
        int path=s[i]-'a';
        if(tree[cur][path]==0)return 0;
        cur=tree[cur][path];
    }
    return pass[cur];
}
void erease(string s)
{
    if(search(s)>0)
    {
        int cur=1;
        for(int i=0;i<s.size();i++)
        {
            int path=s[i]-'a';
            if(--pass[tree[cur][path]]==0)
            {
                tree[cur][path]=0;
                return;
            }
            cur=tree[cur][path];
        }
        e[cur]--;
    }
}
void clear()
{
    for(int i=1;i<=cnt;i++)
    {
        for(int j=0;j<26;j++)
        {
            tree[i][j]=0;
        }
        pass[i]=0;
        e[i]=0;
    }
}
int main()
{
    build();
    insert("apple");
    cout<<search("apple")<<"\n";
    cout<<start("app")<<"\n";
    erease("apple");
    insert("apple");
    cout<<search("apple")<<"\n";
    cout<<start("app")<<"\n";
    clear();
    cout<<start("app")<<"\n";
    return 0;
}