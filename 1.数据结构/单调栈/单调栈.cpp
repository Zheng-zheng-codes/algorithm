#include <bits/stdc++.h>
using namespace std;
int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    vector<int>arr(n);
    vector<vector<int>>ans(n,vector<int>(2));//ans[i][0]:左最小值  ans[i][1]:右最小值
    stack<int>s;
    //单调递增栈求左右最小值
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
        while(!s.empty()&&arr[s.top()]>=arr[i])
        {
            int temp=s.top();
            s.pop();
            if(!s.empty())ans[temp][0]=s.top();
            else ans[temp][0]=-1;
            ans[temp][1]=i;
        }
        s.push(i);
    }
    while(!s.empty())
    {
        int temp=s.top();
        s.pop();
        if(s.empty())ans[temp][0]=-1;
        else ans[temp][0]=s.top();
        ans[temp][1]=-1;
    }
    for(int i=n-1;i>=0;i--)
    {
        if(arr[ans[i][1]]==arr[i])ans[i][1]=ans[ans[i][1]][1];
    }
    for(int i=0;i<n;i++)cout<<ans[i][0]<<" "<<ans[i][1]<<'\n';
    return 0;
}
