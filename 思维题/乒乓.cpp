/*
有 n 个同学轮流在一张桌子上打乒乓球。第 i 个同学的能力值为 ai，能力值两两不同。以下是他们打乒
乓球的规则：
一开始，场上只有一个人，编号是 1。队列 Q = {2, 3, . . . , n} 里从前到后表示当前排队的人。
接下来每一轮，处在队首的选手会弹出队列，并且和场上的人进行乒乓球比赛。进行比赛的时
候，能力值高的人会赢。比赛的败者加入队尾，而胜者留在场上。
但是，为了避免强手一直霸场，他们额外制定了反垄断规则：如果一个人已经连续参加了 n 1 局比
赛，那么接下来的这场比赛会无论如何视作这个人输：他会加入队尾，而对手会留在场上。
他们一共进行了 k 轮比赛，你可以算出每个人参加了多少次比赛吗？
输入
输入包含多组数据。第一行一个正整数 T (1 ≤ T ≤ 10000) 表示数据组数。每个数据的描述如下：
第一行包含两个整数 n, k (3 ≤ n ≤ 2 × 10^5, 1 ≤ k ≤ 10^9)。
第二行包含 n 个整数 a1, a2, . . . , an (1 ≤ ai ≤ 10^9)。
保证所有 ai 都是不同的，并且 T 组数据中 n 的总和不会超过 2 × 10^5。
输出
对于每组数据，输出一行 n 个整数，第 i 个整数表示输入中的第 i 个同学一共参加了多少场比赛。
*/
#include<bits/stdc++.h>
using namespace std;
//由于最强的人对战n-1场后会下去，再打一圈后n-1场最强的人会回来
//所以循环是2n-2场，我们模拟4n场求这个循环节
void solve()
{
    int n,k;
    cin>>n>>k;
    int lim=min(4*n,k);
    vector<int>a(n);
    vector<int>ans(n,0);//用于统计答案
    int ms=0;//ms：最强者的实力
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        ms=max(ms,a[i]);
    }
    queue<int>q;
    int now=0;//now：目前在场上的人
    int tot=0;//tot：一共打了多少场
    for(int i=1;i<n;i++)q.push(i);
    while(lim--)//模拟打了lim场
    {
        k--;
        int x=q.front();
        q.pop();
        ans[now]++;
        ans[x]++;
        if(a[x]>a[now]||tot==n-1)
        {
            q.push(now);
            now=x;
            tot=1;
        }
        else
        {
            q.push(x);
            tot++;
        }
    }
    while(k)
    {
        int x=q.front();
        if(a[x]==ms)break;//当队首是最强者时开始循环
        k--;
        q.pop();
        ans[now]++;
        ans[x]++;
        if(a[x]>a[now]||tot==n-1)
        {
            q.push(now);
            now=x;
            tot=1;
        }
        else
        {
            q.push(x);
            tot++;
        }
    }
    int round=k/(2*n-2);//会打round轮
    k-=(2*n-2)*round;
    for(int i=0;i<n;i++)
    {
        if(i==q.front()||i==now)ans[i]+=n*round;//每一轮的最强者和与他竞争的人（一定是次强者）会打n轮
        else ans[i]+=2*round;//其余人打2轮
    }
    while(k--)//剩下的继续模拟
    {
        int x=q.front();
        q.pop();
        ans[now]++;
        ans[x]++;
        if(a[x]>a[now]||tot==n-1)
        {
            q.push(now);
            now=x;
            tot=1;
        }
        else
        {
            q.push(x);
            tot++;
        }
    }
    for(int i=0;i<n;i++)cout<<ans[i]<<" ";
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)solve();
}