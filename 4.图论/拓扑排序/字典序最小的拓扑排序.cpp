/*
题目描述
有向无环图上有n个点，m条边。求这张图字典序最小的拓扑排序的结果。
字典序最小指希望排好序的结果中，比较靠前的数字尽可能小。
输入格式
第一行是用空格隔开的两个整数n和m，表示n个点和m条边。
接下来是m行，每行用空格隔开的两个数u和v，表示有一条从u到v的边。
输出格式
输出一行，拓扑排序的结果，数字之间用空格隔开
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<int>>tu(n+1);
    vector<int>indeg(n+1,0);
    priority_queue<int,vector<int>,greater<int>>pq;
    vector<int>ans;
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        tu[a].push_back(b);
        indeg[b]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(indeg[i]==0)pq.push(i);
    }
    while(!pq.empty())
    {
        int num=pq.top();
        pq.pop();
        ans.push_back(num);
        for(int i=0;i<tu[num].size();i++)
        {
            if(--indeg[tu[num][i]]==0)
            {
                pq.push(tu[num][i]);
            }
        }
    }
    for(auto i:ans)cout<<i<<" ";
    return 0;
}