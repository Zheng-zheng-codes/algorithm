/*
题目描述
求 n 个四边平行于坐标轴的矩形的面积并。
输入格式
第一行一个正整数 n。
接下来 n 行每行四个非负整数 x1,y1,x2,y2，表示一个矩形的四个端点坐标为 (x1,y1),(x1,y2),(x2,y2),(x2,y1)。
输出格式
一行一个正整数，表示 n 个矩形的并集覆盖的总面积。
*/
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=2e5+10;
struct tree
{
    int all;//总长度
    int len;//覆盖长度
    int num;//覆盖次数
}t[maxn<<2];
int a[maxn];//离散化
struct line
{
    int x;
    int y1;
    int y2;
    int change;
}lin[maxn];
//一个结果转化成两条线
//x1  y1~y2  +1
//x2  y1~y2  -1
static bool cmp(line l1,line l2)
{
    return l1.x<l2.x;
}
void pushup(int k,int l,int r)
{
    if(t[k].num>0)t[k].len=t[k].all;
    else if(l==r)t[k].len=0;
    else t[k].len=t[ls].len+t[rs].len;
}
void build(int k,int l,int r)
{
    t[k].len=0;
    t[k].num=0;
    t[k].all=a[r+1]-a[l];
    if(l==r)return;
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void add(int k,int l,int r,int p,int q,int num)
{
    if(l==p&&r==q)
    {
        t[k].num+=num;
        pushup(k,l,r);
        return;
    }
    int mid=l+r>>1;
    if(q<=mid)add(ls,l,mid,p,q,num);
    else if(p>mid)add(rs,mid+1,r,p,q,num);
    else add(ls,l,mid,p,mid,num),add(rs,mid+1,r,mid+1,q,num);
    pushup(k,l,r);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    int cnt=0;
    int cnt2=0;
    for(int i=0;i<n;i++)
    {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        a[++cnt]=y1;
        a[++cnt]=y2;
        cnt2++;
        lin[cnt2].x=x1;
        lin[cnt2].y1=y1;
        lin[cnt2].y2=y2;
        lin[cnt2].change=1;
        cnt2++;
        lin[cnt2].x=x2;
        lin[cnt2].y1=y1;
        lin[cnt2].y2=y2;
        lin[cnt2].change=-1;
    }
    sort(a+1,a+cnt+1);
    int num=unique(a+1,a+cnt+1)-a-1;
    build(1,1,num);
    sort(lin+1,lin+cnt2+1,cmp);
    int ans=0;
    for(int i=1;i<=cnt2;i++)
    {
        int y1 = lower_bound(a + 1, a + num + 1, lin[i].y1) - a;
        int y2 = lower_bound(a + 1, a + num + 1, lin[i].y2) - a - 1;
        if(i>1)ans+=t[1].len*(lin[i].x-lin[i-1].x);
        add(1,1,num,y1,y2,lin[i].change);
    }
    cout<<ans<<'\n';
    return 0;
}
