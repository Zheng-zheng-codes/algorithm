/*
在这个宇宙中，目前共有 N 个星系，每个星系都有一个能量指数，代表该文明的繁荣程度。
当两个属于不同星系联盟（连通块）的星系想要建立连接时，该连接行动必须由双方联盟中能量指数最高的“领袖星系”来主导。
为了稳定连接两个联盟的超空间虫洞，双方的“领袖星系”必须超负荷运转其核心恒星，释放巨大的能量脉冲。在这个过程中，这两个领袖星系的能量指数会永久衰减为原来的一半（向下取整，例如 10→5, 5→2）。
连接建立后，原来的两个星系联盟将彻底合并为一个新的大联盟，联盟内的所有星系从此共享繁荣，属于同一个连通网络，不再需要建立新的虫洞。
我们也假设每个星系本身就是一个独立的联盟（当它没有与其他星系连接时），且它自己就是该联盟中能量最高的领袖。
你的任务是模拟这一历史进程。
输入描述
第一行输入组数 T，接下来有 T 组数据。
每一组数据有两部分。
第一部分：第一行包含一个整数 N 表示星系的数量。后为 N 行，每行一个数字为第 i 个星系的初始能量指数 si。
第二部分：第一行包含一个整数 M 表示发起了 M 次连接请求。后为 M 行，每行两个整数 x 和 y，表示第 x 个星系和第 y 个星系所在的联盟试图建立连接。
输出描述
对于每次连接请求：
如果第 x 个星系和第 y 个星系已经属于同一个联盟，则连接请求被驳回（因为已经连通），输出 -1。
否则，执行连接操作（双方领袖能量减半并合并联盟），并输出合并后的新联盟中，当前能量指数最高的星系的能量值。
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
int fa[maxn];
int siz[maxn];
int a[maxn];
priority_queue<pii>pq[maxn];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
        siz[i]=1;
        while(!pq[i].empty())pq[i].pop();
        pq[i].push({a[i],i});
    }
}
int find(int n)
{
    while(fa[n]!=n)
    {
        n=fa[n];
    }
    return fa[n];
}
void unit(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy)cout<<-1<<'\n';
    else 
    {
        if(siz[fx]<=siz[fy])
        {
            pii num1=pq[fx].top(),num2=pq[fy].top();
            pq[fx].pop();
            pq[fy].pop();
            fa[num1.second]=fy;
            num1.first/=2;num2.first/=2;
            pq[fy].push(num1);
            pq[fy].push(num2);
            int tmp=pq[fx].size();
            while(tmp--)
            {
                pq[fy].push(pq[fx].top());
                fa[pq[fx].top().second]=fy;
                pq[fx].pop();
            }
            cout<<pq[fy].top().first<<'\n';
            siz[fy]+=siz[fx];
        }
        else
        {
            pii num1=pq[fx].top(),num2=pq[fy].top();
            pq[fx].pop();
            pq[fy].pop();
            fa[num2.second]=fx;
            num1.first/=2;num2.first/=2;
            pq[fx].push(num1);
            pq[fx].push(num2);
            int tmp=pq[fy].size();
            while(tmp--)
            {
                pq[fx].push(pq[fy].top());
                fa[pq[fy].top().second]=fx;
                pq[fy].pop();
            }
            cout<<pq[fx].top().first<<'\n';
            siz[fx]+=siz[fy];
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)
    {
        int n;cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        init(n);
        int m;cin>>m;
        while(m--)
        {
            int num1,num2;cin>>num1>>num2;
            unit(num1,num2);
        }
    }
}