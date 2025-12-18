/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组是数组中的一个连续部分。
*/
#include<bits/stdc++.h>
using namespace std;
int maxSubArray(vector<int>& nums) 
{
    int ans=nums[0];
    int n=nums.size();
    vector<int>dp(n);
    //dp[i]：以i结尾的最大连续累加和
    dp[0]=ans;
    for(int i=1;i<n;i++)
    {
        dp[i]=max(dp[i-1]+nums[i],nums[i]);
        ans=max(ans,dp[i]);
    }
    return ans;
}
int main()
{
    return 0;
}