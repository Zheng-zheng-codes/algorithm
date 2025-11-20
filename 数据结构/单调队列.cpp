#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    int k;cin>>k;
    vector<int>arr(n);
    vector<int>ans;
    deque<int>dq;
    for(int i=0;i<n;i++)cin>>arr[i];
    for(int i=0;i<k;i++)
    {
        //单调递减队列求滑动窗口最大值
        while(!dq.empty()&&arr[dq.back()]<=arr[i])dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(arr[dq.front()]);
    for(int i=0;i+k<n;i++)
    {
        if(dq.front()<i+1)dq.pop_front();
        while(!dq.empty()&&arr[dq.back()]<=arr[i+k])dq.pop_back();
        dq.push_back(i+k);
        ans.push_back(arr[dq.front()]);
    }
    for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
    return 0;
}