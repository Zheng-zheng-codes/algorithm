/*
题目描述
给出 1,2,…,n 的两个排列 P1和 P2，求它们的最长公共子序列。
输入格式
第一行是一个数 n。
接下来两行，每行为 n 个数，为自然数 1,2,…,n 的一个排列。
输出格式
一个数，即最长公共子序列的长度。
*/
#include<bits/stdc++.h>
using namespace std;
int bs(const vector<int>&nums,int len,int num)
{
    int l=0,r=len-1,ans=-1;
    while(l<=r)
    {
        int m=l+r>>1;
        if(nums[m]>=num)
        {
            ans=m;
            r=m-1;
        }
        else l=m+1;
    }
    return ans;
}
//将第一个数组里的数所处的下标存在map中，
//接下来将第二个数组的数与下标对应形成一个数组
//求出这个数组的最长递增子序列即可
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    unordered_map<int,int>um;
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        um[a[i]]=i;
    }
    vector<int>b(n);
    vector<int>nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        nums[i]=um[b[i]];
    }
    vector<int>e(n);
    int len=0;
    for(int i=0;i<n;i++)
    {
        int tmp=bs(e,len,nums[i]);
        if(tmp==-1)e[len++]=nums[i];
        else e[tmp]=nums[i];
    }
    cout<<len;
    return 0;
}