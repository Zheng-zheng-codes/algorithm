/*
题目描述
蒟蒻 HansBug 在一本数学书里面发现了一个神奇的数列，包含 N 个实数。他想算算这个数列的平均数和方差。
输入格式
第一行包含两个正整数 N,M，分别表示数列中实数的个数和操作的个数。
第二行包含 N 个实数，其中第 i 个实数表示数列的第 i 项。
接下来 M 行，每行为一条操作，格式为以下三种之一：
操作 1：1 x y k ，表示将第 x 到第 y 项每项加上 k，k 为一实数。
操作 2：2 x y ，表示求出第 x 到第 y 项这一子数列的平均数。
操作 3：3 x y ，表示求出第 x 到第 y 项这一子数列的方差。
输出格式
输出包含若干行，每行为一个实数，即依次为每一次操作 2 或操作 3 所得的结果（所有结果四舍五入保留 4 位小数）。
*/
#include<bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=1e5+10;
double a[maxn];
struct tree
{
    double sum1;
    double sum2;
    double lz;
    tree(){lz=0;}
}t[maxn<<2];
void pushup(int k)
{
    t[k].sum1=t[ls].sum1+t[rs].sum1;
    t[k].sum2=t[ls].sum2+t[rs].sum2;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        t[k].sum1=a[l];
        t[k].sum2=pow(a[l],2);
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
}
void puttag(int k,int l,int r,double val)
{
    t[k].sum2+=2*val*t[k].sum1+(r-l+1)*pow(val,2);
    t[k].sum1+=val*(r-l+1);
    t[k].lz+=val;
}
void pushdown(int k,int l,int r)
{
    if(t[k].lz)
    {
        int mid=l+r>>1;
        puttag(ls,l,mid,t[k].lz);
        puttag(rs,mid+1,r,t[k].lz);
        t[k].lz=0;
    }
}
void modify(int k,int l,int r,int p,int q,double val)
{
    if(l==p&&r==q)
    {
        puttag(k,l,r,val);
        return;
    }
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)modify(ls,l,mid,p,q,val);
    else if(p>mid)modify(rs,mid+1,r,p,q,val);
    else modify(ls,l,mid,p,mid,val),modify(rs,mid+1,r,mid+1,q,val);
    pushup(k);
}
double query(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum1;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query(ls,l,mid,p,q);
    else if(p>mid)return query(rs,mid+1,r,p,q);
    else return query(ls,l,mid,p,mid)+query(rs,mid+1,r,mid+1,q);
}
double query2(int k,int l,int r,int p,int q)
{
    if(l==p&&r==q)return t[k].sum2;
    pushdown(k,l,r);
    int mid=l+r>>1;
    if(q<=mid)return query2(ls,l,mid,p,q);
    else if(p>mid)return query2(rs,mid+1,r,p,q);
    else return query2(ls,l,mid,p,mid)+query2(rs,mid+1,r,mid+1,q);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1)
        {
            double k;
            cin>>k;
            modify(1,1,n,x,y,k);
        }
        else if(op==2)
        {
            cout<<fixed<<setprecision(4)<<query(1,1,n,x,y)/(y-x+1)<<'\n';
        }
        else
        {
            double num1=query2(1,1,n,x,y)/(y-x+1);
            double num2=query(1,1,n,x,y)/(y-x+1);
            cout<<fixed<<setprecision(4)<<num1-pow(num2,2)<<'\n';
        }
    }
    return 0;
}
