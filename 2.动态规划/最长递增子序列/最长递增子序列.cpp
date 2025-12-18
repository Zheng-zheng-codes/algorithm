#include<bits/stdc++.h>
using namespace std;
//暴力方法O（n^2）
int lengthOfLIS(vector<int>& nums) 
{
    int ans=1;
    int n=nums.size();
    vector<int>dp(n,1);
    //dp[i]:以i结尾的最长递增子序列
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i])
            {
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        ans=max(ans,dp[i]);
    }
    return ans;
}
//在ends的前len长度中找第一个>=num的数(二分查找)
//ends数组一定是单调递增的
int bf1(const vector<int>&ends,int len,int num)
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
//优化方法O（nlogn）
int lengthOfLIS(vector<int>& nums) 
{
    int n=nums.size();
    vector<int>ends(n);
    //ends[i]:长度为i+1的递增子序列的最小结尾
    //答案即为ends数组用到的长度
    int len=0;//[0…len-1]是有效的
    for(int i=0;i<n;i++)
    {
        int num=bf1(ends,len,nums[i]);
        if(num==-1)ends[len++]=nums[i];
        else ends[num]=nums[i];
    }
    return len;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    return 0;
}