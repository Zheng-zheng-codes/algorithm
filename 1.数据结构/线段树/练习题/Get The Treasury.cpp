//https://acm.hdu.edu.cn/showproblem.php?pid=3642
#include<bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int maxn=2010;
struct area
{
    int x1,x2,y,z1,z2,change;
    bool operator<(area&other)const
    {
        return y<other.y;
    }
}seg[maxn],tmp[maxn];
int xs[maxn];
int zs[maxn];
struct tree
{
    int s;//区域完全覆盖的次数（懒标记）
    int once;//覆盖一次的长度
    int twice;//覆盖两次的长度
    int more;//覆盖更多次的长度
}t[maxn<<2];
void pushup(int k,int l,int r)
{
    if(t[k].s>=3)
    {
        t[k].more=xs[r+1]-xs[l];
        t[k].once=t[k].twice=0;
    }
    else if(t[k].s==2)
    {
        if(l==r)
        {
            t[k].twice=xs[r+1]-xs[l];
            t[k].once=t[k].more=0;
        }
        else 
        {
            t[k].more=t[ls].once+t[ls].twice+t[ls].more+t[rs].once+t[rs].twice+t[rs].more;
            t[k].twice=xs[r+1]-xs[l]-t[k].more;
            t[k].once=0;
        }
    }
    else if(t[k].s==1)
    {
        if(l==r)
        {
            t[k].once=xs[r+1]-xs[l];
            t[k].twice=t[k].more=0;
        }
        else
        {
            t[k].more=t[ls].twice+t[ls].more+t[rs].twice+t[rs].more;
            t[k].twice=t[ls].once+t[rs].once;
            t[k].once=xs[r+1]-xs[l]-t[k].more-t[k].twice;
        }
    }
    else
    {
        if(l==r)t[k].more=t[k].twice=t[k].once=0;
        else
        {
            t[k].more=t[ls].more+t[rs].more;
            t[k].twice=t[ls].twice+t[rs].twice;
            t[k].once=t[ls].once+t[rs].once;
        }
    }
}
void build(int k,int l,int r)
{
    t[k].s=t[k].once=t[k].twice=t[k].more=0;
    if(l==r)return;
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void add(int k,int l,int r,int p,int q,int num)
{
    if(l==p&&r==q)
    {
        t[k].s+=num;
        pushup(k,l,r);
        return;
    }
    int mid=l+r>>1;
    if(mid>=q)add(ls,l,mid,p,q,num);
    else if(mid<p)add(rs,mid+1,r,p,q,num);
    else add(ls,l,mid,p,mid,num),add(rs,mid+1,r,mid+1,q,num);
    pushup(k,l,r);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        cout<<"Case "<<i<<": ";
        int m;cin>>m;
        int cnt=0,cnt2=0,cnt3=0;
        while(m--)
        {
            int x1,y1,z1,x2,y2,z2;
            cin>>x1>>y1>>z1>>x2>>y2>>z2;
            cnt++;
            seg[cnt].x1=x1;
            seg[cnt].x2=x2;
            seg[cnt].y=y1;
            seg[cnt].z1=z1;
            seg[cnt].z2=z2;
            seg[cnt].change=1;
            cnt++;
            seg[cnt].x1=x1;
            seg[cnt].x2=x2;
            seg[cnt].y=y2;
            seg[cnt].z1=z1;
            seg[cnt].z2=z2;
            seg[cnt].change=-1;
            xs[++cnt2]=x1;
            xs[++cnt2]=x2;
            zs[++cnt3]=z1;
            zs[++cnt3]=z2;
        }
        sort(xs+1,xs+cnt2+1);
        int num1=unique(xs+1,xs+1+cnt2)-xs-1;
        sort(zs+1,zs+cnt3+1);
        int num2=unique(zs+1,zs+cnt3+1)-zs-1;
        int ans=0;
        for(int aaa=1;aaa<num2;++aaa)//遍历每一个z的区间（zs[aaa]~zs[aaa+1]）
        {
            int tot=0;
            for(int bbb=1;bbb<=cnt;++bbb)
            {
                if(seg[bbb].z1<=zs[aaa]&&seg[bbb].z2>zs[aaa])tmp[++tot]=seg[bbb];
                //存储完全覆盖下边界的
            }
            sort(tmp+1,tmp+tot+1);
            build(1,1,num1-1);//num个点-->num-1个区间
            int area=0;
            for(int bbb=1;bbb<tot;++bbb)
            {
                int l=lower_bound(xs+1,xs+num1+1,tmp[bbb].x1)-xs;
                int r=lower_bound(xs+1,xs+num1+1,tmp[bbb].x2)-xs-1;
                add(1,1,num1-1,l,r,tmp[bbb].change);
                area+=t[1].more*(tmp[bbb+1].y-tmp[bbb].y);
            }
            ans+=area*(zs[aaa+1]-zs[aaa]);
        }
        cout<<ans<<'\n';
    }
}