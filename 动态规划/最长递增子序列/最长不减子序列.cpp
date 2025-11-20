#include<bits/stdc++.h>
using namespace std;
int bf1(const vector<int>&ends,int len,int num)
{
    int l=0,r=len-1;
    int ans=-1;
    while(l<=r)
    {
        int m=l+r>>1;
        if(ends[m]>num)
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