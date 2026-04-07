//https://www.lanqiao.cn/problems/1624/learning/?page=1&first_category_id=1&name=%E5%B0%8F%E8%93%9D%E5%90%83%E7%B3%96%E6%9E%9C
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    priority_queue<int>pq;
    int n;cin>>n;
    for(int i=0;i<n;++i)
    {
        int num;cin>>num;
        pq.push(num);
    }
    while(!pq.empty())
    {
        if(pq.size()==1&&pq.top()!=1)
        {
            cout<<"No";
            return;
        }
        if(pq.size()==1)break;
        int num1=pq.top();
        pq.pop();
        int num2=pq.top();
        pq.pop();
        num1-=num2;
        if(num1)pq.push(num1);
    }
    cout<<"Yes";
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
}