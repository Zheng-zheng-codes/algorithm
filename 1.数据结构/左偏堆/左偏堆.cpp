//https://www.luogu.com.cn/problem/P3377
#include<bits/stdc++.h>
#define ptr shared_ptr<node>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e5+10;
int fa[maxn];
void init(int n)
{
    for(int i=1;i<=n;i++)fa[i]=i;
}
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void unit(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy)return;
    fa[fx]=fy;
}
struct node
{
    int key;
    int idx;
    int rank;
    ptr left,right;
    node(int k,int i):key(k),idx(i),rank(1),left(NULL),right(NULL){}
    node(int k,int i,ptr l,ptr r):key(k),idx(i),left(l),right(r)
    {
        rank=(r?r->rank:0)+1;
    }
};
class leftheap
{
private:
    ptr root;
    static ptr merge(ptr h1,ptr h2)
    {
        if(!h1)return h2;
        if(!h2)return h1;
        if(h1->key>h2->key)swap(h1,h2);
        if(h1->key==h2->key&&h1->idx>h2->idx)swap(h1,h2);
        ptr new_l=h1->left;
        ptr new_r=merge(h1->right,h2);
        int left_r=(new_l?new_l->rank:0)+1;
        int right_r=(new_r?new_r->rank:0)+1;
        if(left_r<right_r)swap(new_l,new_r);
        ptr ans=make_shared<node>(h1->key,h1->idx,new_l,new_r);
        return ans;
    }
    int siz(ptr root) 
    {
        if(!root)return 0;
        return 1+siz(root->left)+siz(root->right);
    }
    void collect(ptr node,vector<int>&res) 
    {
        if(!node)return;
        res.push_back(node->key);
        collect(node->left,res);
        collect(node->right,res);
    }
public:
    leftheap():root(NULL){}
    leftheap(ptr r):root(r){}
    void insert(int val,int i) 
    {
        ptr new_node = make_shared<node>(val,i);
        root=merge(root,new_node);
    }
    pii peek() 
    {
        return {root->key,root->idx};
    }
    void pop() 
    {
        root=merge(root->left,root->right);
    }
    void unit( leftheap&other) 
    {
        root=merge(other.root,root);
    }
    bool empty() 
    {
        return root==NULL;
    }
    int size() 
    {
        return siz(root);
    }
    vector<int> dump() 
    {
        vector<int>ans;
        collect(root,ans);
        sort(ans.begin(),ans.end());
        return ans;
    }
};
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    vector<int>arr(n+1);
    vector<leftheap>lh(n+1);
    vector<bool>jud(n+1,0);
    init(n);
    for(int i=1;i<=n;i++)
    {
        cin>>arr[i];
        ptr r=make_shared<node>(arr[i],i);
        lh[i]=leftheap(r);
    }
    while(m--)
    {
        int op;cin>>op;
        if(op==1)
        {
            int x,y;cin>>x>>y;
            if(jud[x]||jud[y])continue;
            int fx=find(x),fy=find(y);
            if(fx==fy)continue;
            unit(fx,fy);
            lh[fx].unit(lh[fy]);
            lh[fy]=lh[fx];
        }
        else
        {
            int x;cin>>x;
            if(jud[x])
            {
                cout<<-1<<'\n';
                continue;
            }
            int fx=find(x);
            if(lh[fx].empty())
            {
                cout<<-1<<'\n';
                continue;
            }
            pii top=lh[fx].peek();
            cout<<top.first<<'\n';
            lh[fx].pop();
            jud[top.second]=1;
        }
    }
}
