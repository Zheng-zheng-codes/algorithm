#include<bits/stdc++.h>
#define ptr shared_ptr<node>
using namespace std;
struct node
{
    int key;
    int rank;
    ptr left,right;
    node(int k):key(k),rank(1),left(NULL),right(NULL){}
    node(int k,ptr l,ptr r):key(k),left(l),right(r)
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
        ptr new_l=h1->left;
        ptr new_r=merge(h1->right,h2);
        int left_r=(new_l?new_l->rank:0)+1;
        int right_r=(new_r?new_r->rank:0)+1;
        if(left_r<right_r)swap(new_l,new_r);
        ptr ans=make_shared<node>(h1->key,new_l,new_r);
        return ans;
    }
    int siz(ptr root) const
    {
        if(!root)return 0;
        return 1+siz(root->left)+siz(root->right);
    }
    void collect(ptr node,vector<int>&res) const
    {
        if(!node)return;
        res.push_back(node->key);
        collect(node->left,res);
        collect(node->right,res);
    }
public:
    leftheap():root(NULL){}
    leftheap(ptr r):root(r){}
    leftheap insert(int val) const
    {
        ptr new_node = make_shared<node>(val);
        return leftheap(merge(root,new_node));
    }
    int peek() const
    {
        return root->key;
    }
    leftheap pop() const
    {
        return leftheap(merge(root->left,root->right));
    }
    leftheap unit(const leftheap&other) const
    {
        return leftheap(merge(other.root,root));
    }
    bool empty() const
    {
        return root==NULL;
    }
    int size() const
    {
        return siz(root);
    }
    vector<int> dump() const
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
    int q;cin>>q;
    unordered_map<string,leftheap>um;
    while(q--)
    {
        string ask;cin>>ask;
        if(ask=="NEW")
        {
            string v;cin>>v;
            if(um.count(v))cout<<"ERROR"<<'\n';
            else um[v]=leftheap();
        }
        else if(ask=="INSERT")
        {
            string v,arrow,v_new;
            int num;
            cin>>v>>num>>arrow>>v_new;
            if(!um.count(v)||um.count(v_new))cout<<"ERROR"<<'\n';
            else um[v_new]=um[v].insert(num);
        }
        else if(ask=="PEEK")
        {
            string v;cin>>v;
            if(!um.count(v))cout<<"ERROR"<<'\n';
            else 
            {
                if(um[v].empty())cout<<"EMPTY"<<'\n';
                else cout<<um[v].peek()<<'\n';
            }
        }
        else if(ask=="POP")
        {
            string v,arrow,v_new;
            cin>>v>>arrow>>v_new;
            if(!um.count(v)||um.count(v_new))cout<<"ERROR"<<'\n';
            else
            {
                if(um[v].empty())cout<<"EMPTY"<<'\n';
                else um[v_new]=um[v].pop();
            }
        }
        else if(ask=="UNION")
        {
            string v1,v2,arrow,v_new;
            cin>>v1>>v2>>arrow>>v_new;
            if(!um.count(v1)||!um.count(v2)||um.count(v_new))cout<<"ERROR"<<'\n';
            else um[v_new]=um[v1].unit(um[v2]);
        }
        else if(ask=="SIZE")
        {
            string v;cin>>v;
            if(!um.count(v))cout<<"ERROR"<<'\n';
            else cout<<um[v].size()<<'\n';
        }
        else if(ask=="ISEMPTY")
        {
            string v;cin>>v;
            if(!um.count(v))cout<<"ERROR"<<'\n';
            else 
            {
                if(um[v].empty())cout<<"YES"<<'\n';
                else cout<<"NO"<<'\n';
            }
        }
        else if(ask=="FROMLIST")
        {
            string v,lists,arrow,v_new;
            cin>>v>>lists>>arrow>>v_new;
            if(!um.count(v)||um.count(v_new))cout<<"ERROR"<<'\n';
            else
            {
                leftheap h=um[v];
                if (lists.size() > 2) 
                {
                    string inner = lists.substr(1, lists.size() - 2);
                    if (!inner.empty()) 
                    {
                        stringstream ss(inner);
                        string token;
                        while (getline(ss, token, ',')) 
                        {
                            if (token.empty()) continue;
                            int val = stoll(token);
                            h = h.insert(val); 
                        }
                    }
                }
                um[v_new]=h;
            }
        }
        else if(ask=="DUMP")
        {
            string v;cin>>v;
            if(!um.count(v))cout<<"ERROR"<<'\n';
            else
            {
                auto ans=um[v].dump();
                cout<<'[';
                for(int i=0;i<ans.size();i++)
                {
                    if(i)cout<<',';
                    cout<<ans[i];
                }
                cout<<"]\n";
            }
        }
        else cout<<"ERROR"<<'\n';
    }
}
