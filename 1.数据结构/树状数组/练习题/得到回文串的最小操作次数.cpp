//https://leetcode.cn/problems/minimum-number-of-moves-to-make-palindrome/
//贪心：从左往右遍历的同时把先遇到的尽量往左排（可以通过分类讨论证明）
//首先统计每个字符出现的位置
//树状数组：
//原数组：最开始每一位都是1，分配的时候进行遍历，先遇见的往最左边排（前缀和即为以前排过的数字个数即当前数字要排的位置）
//排完左边的把右边没排的同字符也排好，同时把原数组的这一位变成0
#include<bits/stdc++.h>
using namespace std;
vector<int>cnt[26];
int tree[2050];
int where[2050];//最终分配的每个字符的位置（逆序数即为答案）
int n;
int tmp[2050];
void add(int pos,int num)
{
    while(pos<=n)
    {
        tree[pos]+=num;
        pos+=pos&(-pos);
    }
}
int query(int pos)
{
    int ans=0;
    while(pos>0)
    {
        ans+=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
int ni(int l,int r)
{
    if(l==r)return 0;
    int mid=l+r>>1;
    int ans=ni(l,mid)+ni(mid+1,r);
    int k=0;
    int i=l,j=mid+1;
    while(i<=mid&&j<=r)
    {
        if(where[i]>where[j])
        {
            ans+=(mid-i+1);
            tmp[k++]=where[j];
            ++j;
        }
        else
        {
            tmp[k++]=where[i];
            ++i;
        }
    }
    while(i<=mid)
    {
        tmp[k++]=where[i];
        ++i;
    }
    while(j<=r)
    {
        tmp[k++]=where[j];
        ++j;
    }
    k=l;
    for(int x=0;x<r-l+1;++x,++k)where[k]=tmp[x];
    return ans;
}
int minMovesToMakePalindrome(string s) 
{
    memset(tree,0,sizeof(tree));
    memset(where,0,sizeof(where));
    memset(tmp,0,sizeof(tmp));
    n=s.size();
    s='0'+s;
    for(int i=1;i<=n;++i)
    {
        add(i,1);
        cnt[s[i]-'a'].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        if(where[i])continue;
        int temp=cnt[s[i]-'a'].back();
        if(i==temp)
        {
            where[i]=1+n>>1;
            add(i,-1);
            continue;
        }
        where[i]=query(i);
        where[temp]=n-where[i]+1;
        add(temp,-1);
        cnt[s[i]-'a'].pop_back();
    }
    return ni(1,n);
}