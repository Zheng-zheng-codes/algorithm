/*
查尔斯兔子喜欢吃草。俗话说，兔子不吃窝边草。因此，查尔斯每天都要离开自己的兔子窝去找草吃。
有一天，查尔斯来到一个二维平面上，这里有许多不同的点。他可以选择一个点 A 和另外四个点 B、C、D、E，
把这四个点与 A 分别连接，构成四条线段。我们称这四条线段为“一丛草”，当且仅当它们满足以下条件：
四条线段中，任意两条线段仅在点 A 相交。
输入格式
第一行包含一个整数 T（1 ≤ T ≤ 120），表示测试用例的数量。
每个测试用例的第一行包含一个整数 n（1 ≤ n ≤ 25000），表示这个测试用例中点的数量。
接下来的 n 行，每行包含两个整数 x 和 y（−10⁷ ≤ x, y ≤ 10⁷），表示一个点的坐标 (x, y)。保证所有点都互不相同。
保证所有测试用例中 n 的总和不超过 10⁵。
输出格式
对于每个测试用例：
如果不存在一丛草，输出一行 NO；
否则，输出一行 YES，接着输出五行，每行两个整数：
第一行为点 A 的坐标；
接下来的四行分别为点 B、C、D、E 的坐标（顺序不限）。
如果存在多个满足条件的“一丛草”，可以输出任意一个。
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=25010;
long long a[maxn],b[maxn];
typedef long long ll;
bool pan(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3,ll x4,ll y4,ll x5,ll y5)
{
	if((x2-x1)*(y3-y1)!=(x3-x1)*(y2-y1)) return 0;
	if((x2-x1)*(y4-y1)!=(x4-x1)*(y2-y1)) return 0;
	if((x2-x1)*(y5-y1)!=(x5-x1)*(y2-y1)) return 0;
	return 1;
}//判断五点共线（不共线的五点就可以满足要求）
bool on(int x1,int y1,int x2,int y2,int x3,int y3)
{
    int maxx,minx,maxy,miny;
    maxx = max(x1,x2);
    minx = min(x1,x2);
    maxy = max(y1,y2);
    miny = min(y1,y2);
    if(!(x3>=minx&&x3<=maxx&&y3>=miny&&y3<=maxy)) return 0; 
    if((x3-x1)*(y2-y1)==(x2-x1)*(y3-y1)) return 1; 
    return 0;
}//判断第三个点是否在前两个点的线段上
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	if(n<5)
	{
	    cout<<"NO"<<'\n';
		return;
	}
	ll x1=a[1],y1=b[1];
	ll x2=a[2],y2=b[2];
	ll x3=a[3],y3=b[3];
	ll x4=a[4],y4=b[4];
	for(int i=5;i<=n;i++)
	{
		ll x5=a[i],y5=b[i];
		if(!pan(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5))
		{
			cout<<"YES"<<'\n';
			ll x[8]={x1,x2,x3,x4,x5};
			ll y[8]={y1,y2,y3,y4,y5};
			for(int j=0;j<5;j++)
			{
				int f=1;
				for(int z=0;z<5;z++)
				{
					if(z==j) continue;
					for(int p=0;p<5;p++)
					{
						if(p==z||p==j) continue;
						if(on(x[j],y[j],x[z],y[z],x[p],y[p]))
						{
							f=0;
							break;
						}
					}
					if(!f) break;
				}
				if(f)
				{
					cout<<x[j]<<" "<<y[j]<<'\n';
					for(int p=0;p<5;p++)
					{
						if(p!=j) cout<<x[p]<<" "<<y[p]<<'\n';
					}
					return;
				}
			}
		}
	}
	cout<<"NO"<<'\n';
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}