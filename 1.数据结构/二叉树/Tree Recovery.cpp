//http://poj.org/problem?id=2255
//根据前序遍历和后序遍历构造树求中序遍历
#include<bits/stdc++.h>
using namespace std;
struct treenode
{
    char c;
    treenode*left;
    treenode*right;
    treenode(){left=right=NULL;}
};
treenode* build(string&s1,string&s2)
{
    treenode*root=new(treenode);
    char ch=s1[0];
    root->c=ch;
    if(s1.size()==1)return root;
    int num;
    for(int i=0;i<s2.size();++i)
    {
        if(s2[i]==ch)
        {
            num=i;
            break;
        }
    }
    string ls1=s1.substr(1,num);
    string ls2=s2.substr(0,num);
    string rs1=s1.substr(1+num);
    string rs2=s2.substr(1+num);
    if(ls1.size())root->left=build(ls1,ls2);
    if(rs1.size())root->right=build(rs1,rs2);
    return root;
}
void ans(treenode*root)
{
    if(root==NULL)return;
    ans(root->left);
    ans(root->right);
    cout<<root->c;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    string s1,s2;
    while(cin>>s1>>s2)
    {
        treenode*root=build(s1,s2);
        ans(root);
        cout<<'\n';
    }
}