//https://www.luogu.com.cn/problem/P1908
//归并分治方法
//本题还可以使用树状数组，详见1.数据结构/树状数组/练习题
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
int a[maxn];
int tmp[maxn];
int ni(int l,int r)
{
    if(l==r)return 0;
    int mid=l+r>>1;
    int ans=ni(l,mid)+ni(mid+1,r);
    int k=0;
    int i=l,j=mid+1;
    while(i<=mid&&j<=r)
    {
        if(a[i]>a[j])
        {
            ans+=(mid-i+1);
            tmp[k++]=a[j];
            ++j;
        }
        else
        {
            tmp[k++]=a[i];
            ++i;
        }
    }
    while(i<=mid)
    {
        tmp[k++]=a[i];
        ++i;
    }
    while(j<=r)
    {
        tmp[k++]=a[j];
        ++j;
    }
    k=l;
    for(int x=0;x<r-l+1;++x,++k)a[k]=tmp[x];
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    cout<<ni(1,n);
}