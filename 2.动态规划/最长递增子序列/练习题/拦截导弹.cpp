//https://www.luogu.com.cn/problem/P1020
//第一问即为最长不增子序列
//第二问即为最长递增子序列
#include<bits/stdc++.h>
using namespace std;
int bf1(const vector<int>&ends,int len,int num)
{
    int l=0,r=len-1;
    int ans=-1;
    while(l<=r)
    {
        int m=l+r>>1;
        if(ends[m]<num)
        {
            ans=m;
            r=m-1;
        }
        else l=m+1;
    }
    return ans;
}
int lengthOfLIS(vector<int>& nums) 
{
    int n=nums.size();
    vector<int>ends(n);
    int len=0;
    for(int i=0;i<n;i++)
    {
        int num=bf1(ends,len,nums[i]);
        if(num==-1)ends[len++]=nums[i];
        else ends[num]=nums[i];
    }
    return len;
}
int bf2(const vector<int>&ends,int len,int num)
{
    int l=0,r=len-1;
    int ans=-1;
    while(l<=r)
    {
        int m=l+r>>1;
        if(ends[m]>=num)
        {
            ans=m;
            r=m-1;
        }
        else l=m+1;
    }
    return ans;
}
int lengthOfLIS2(vector<int>& nums) 
{
    int n=nums.size();
    vector<int>ends(n);
    int len=0;
    for(int i=0;i<n;i++)
    {
        int num=bf2(ends,len,nums[i]);
        if(num==-1)ends[len++]=nums[i];
        else ends[num]=nums[i];
    }
    return len;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    vector<int>nums;
    int num;
    while(cin>>num)nums.push_back(num);
    cout<<lengthOfLIS(nums)<<'\n';
    cout<<lengthOfLIS2(nums)<<'\n';
    return 0;
}