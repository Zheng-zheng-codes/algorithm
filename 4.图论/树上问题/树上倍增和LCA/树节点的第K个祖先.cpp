//https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/
#include<bits/stdc++.h>
using namespace std;
class TreeAncestor {
public:
    int st[50001][16];//st[i][j]:从节点i往上走2^j步能走到的位置(走不到设为-1)
    TreeAncestor(int n, vector<int>& parent) {
        memset(st,-1,sizeof(st));
        for(int i=0;i<n;++i)
        {
            st[i][0]=parent[i];
        }
        int power=(int)log2(n);
        for(int p=1;p<=power;++p)
        {
            for(int i=0;i<n;++i)
            {
               if(st[i][p-1]!=-1)st[i][p]=st[st[i][p-1]][p-1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        int power=(int)log2(k);
        for(int p=power;p>=0;--p)
        {
            int tmp=(1<<p);
            if(k>=tmp)
            {
                node=st[node][p];
                if(node==-1)return -1;
                k-=tmp;
            }
        }
        return node;
    }
};