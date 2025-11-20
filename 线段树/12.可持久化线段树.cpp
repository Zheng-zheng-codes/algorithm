#include<bits/stdc++.h>//洛谷P3919可持久化线段树模板题 
#define int long long//这道题时间卡得非常紧张，如果不加快读，大概率会TLE 
#define pub push_back//第一次使用快读，也由此知道快读和cin完全不可兼容 
#define pob pop_back//经测试c语言读入没有快读要快 
using namespace std;
typedef pair<int,int>pii;
const int N=4e7+10;//理论上空间需要O(nlogn)(学长建议开30~60倍保险) 
int n,m,root[1000010];//每个版本的头结点 
int cnt=0;//当前最新版本，root的顶部指针 
int id=0;//tree的顶部指针 
int arr[1000010];//存初始数据 
inline void read(int& x) {//这个函数只能用于读整数 
	int s=0,w=1; char ch=getchar ( ) ;
	while ( ch<'0' || ch>'9' ) { if ( ch=='-'  )w=-1; ch=getchar ( ) ; }
	while ( ch>='0'&&ch<='9' ) {
		s=(s *10)+ch - '0'; // s=(( s *10)+ch - ’ 0 ’ )%mod; 在 快 读 时 取模
		ch=getchar ( ) ;
	}
	x=s *w;
}
struct Tree{
	int l,r,ls,rs,sum;//这道题仅需单点修改，就没有上懒标记 
}tree[N];
void pushup(int x){
	tree[x].sum=tree[tree[x].ls].sum+tree[tree[x].rs].sum;
}
void build(int x){//注意这里的build没有用动态开点，是正常一般的建树，这样会导致时间和空间常数大一些，所以才被迫用快读 
	id=max(id,x);//id是tree的最新指针，所以这里更新其为最大值 
	int l=tree[x].l,r=tree[x].r;
	if(l==r){
		tree[x].sum=arr[l];
		return;
	}
	int mid=l+r>>1;//一开始建树的儿子生成方式和以前是一样的  
	int ls=x<<1,rs=x<<1|1;
	tree[x].ls=ls,tree[x].rs=rs;
	tree[ls].l=l,tree[ls].r=mid;
	tree[rs].l=mid+1,tree[rs].r=r;
	build(ls),build(rs);
	pushup(x);
}
void modify(int x,int c,int val){//注意这里仅是单点修改 
	int l=tree[x].l,r=tree[x].r;
	int ls=tree[x].ls,rs=tree[x].rs;
	if(l==r){
		int temp=++id;
		tree[temp]=tree[x];
		tree[temp].sum=val;
		return;
	}
	int temp=++id;
	tree[temp]=tree[x];
	int mid=l+r>>1;
	if(mid>=c)tree[temp].ls=1+id,modify(ls,c,val);
	else tree[temp].rs=id+1,modify(rs,c,val);
	pushup(temp);
}
int query1(int x,int c){//仅是单点查询，不过这道题只要求单点查询 
	if(tree[x].l==tree[x].r)return tree[x].sum;
	int ls=tree[x].ls,rs=tree[x].rs;
	int l=tree[x].l,r=tree[x].r;
	int mid=l+r>>1;
	if(mid>=c)return query1(ls,c);
	else return query1(rs,c);
}
int query(int x,int left,int right){//查询区间和 
	int l=tree[x].l,r=tree[x].r;
	int ls=tree[x].ls,rs=tree[x].rs;
	int mid=l+r>>1;
	if(l==left&&r==right)return tree[x].sum;
	else if(mid<left)return query(rs,left,right);
	else if(mid+1>right)return query(ls,left,right);
	else return query(ls,left,mid)+query(rs,mid+1,right);
}
void solve() {
//	n=read(),m=read();
//	for(int i=1;i<=n;i++)cin>>arr[i];
    read(n),read(m);
	for(int i=1;i<=n;i++)read(arr[i]);
	root[++cnt]=1;
	tree[1].l=1,tree[1].r=n;
	build(1);//一开始建树没什么区别  
	while(m--){
		int a,op,c,d;
//		cin>>a>>op>>c;
		read(a),read(op),read(c);
		a++;//题目以0为起始版本，我这里以1开始 
		if(op==1){
//			cin>>d;
			read(d);root[++cnt]=id+1;
			modify(root[a],c,d);//a版本，c位改为d,新版本的根 
		}
		else cnt++,root[cnt]=root[a],cout<<query(root[a],c,c)/*<<' '<<a<<' '<<root[a]*/<<'\n';//a版本，查c位
	}
}
signed main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--) {
//		shuru();//这个题要边输入边处理，不方便分离，所以就不要这个函数了 
		solve();
	}
	return 0;
}
