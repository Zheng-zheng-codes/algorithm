//https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
#include<bits/stdc++.h>
using namespace std;
const int maxn=2050;
int tree[maxn];//用来记录最大长度 tree[i]:以i管辖范围内结尾的数结尾的最长递增子序列长度
int tree2[maxn];//用来记录出现次数 tree2[i]:长度出现的次数
int cnt;
//用来更新管辖范围内有pos的部分
void add(int pos,int len,int num)
{
    while(pos<=cnt)
    {
        if(tree[pos]==len)tree2[pos]+=num;
        else if(tree[pos]<len)
        {
            tree[pos]=len;
            tree2[pos]=num;
        }
        pos+=pos&(-pos);
    }
}
//用来查询pos位置以前的最长递增子序列和出现次数
int len,num;
void query(int pos)
{
    len=num=0;
    while(pos>0)
    {
        if(tree[pos]==len)num+=tree2[pos];
        else if(tree[pos]>len)
        {
            num=tree2[pos];
            len=tree[pos];
        }
        pos-=pos&(-pos);
    }
}
int findNumberOfLIS(vector<int>& nums) 
{
    vector<int>tmp;
    for(int i=0;i<nums.size();++i)tmp.push_back(nums[i]);
    sort(tmp.begin(),tmp.end());
    cnt=unique(tmp.begin(),tmp.end())-tmp.begin();
    unordered_map<int,int>um;
    for(int i=0;i<cnt;++i)um[tmp[i]]=i+1;
    for(int i=0;i<nums.size();++i)
    {
        query(um[nums[i]]-1);
        if(len==0)add(um[nums[i]],1,1);
        else add(um[nums[i]],len+1,num);
    }
    query(um[tmp[cnt-1]]);
    return num;
}