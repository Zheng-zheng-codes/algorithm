//https://www.lanqiao.cn/problems/3504/learning/?page=1&first_category_id=1
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
vector<int>tu[maxn];
int color[maxn];
int ans;
unordered_map<int,int>dfs(int root)
{
    unordered_map<int,int>um;
    um[color[root]]++;
    for(int i=0;i<tu[root].size();++i)
    {
        int tmp=tu[root][i];
        unordered_map<int,int>col=dfs(tmp);
        if(col.size()>um.size())swap(um,col);//小并大
        for(auto it:col)
        {
            um[it.first]+=col[it.first];
        }
    }
    int cnt=0;
    bool jud=0;
    for(auto it:um)
    {
        if(cnt==0)cnt=it.second;
        else if(cnt!=it.second)
        {
            jud=1;
            break;
        }
    }
    if(!jud)ans++;
    return um;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        int fa;cin>>color[i]>>fa;
        tu[fa].push_back(i);
    }
    dfs(1);
    cout<<ans;
}