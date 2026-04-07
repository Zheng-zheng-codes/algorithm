#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    vector<int>vec={1,2,2,3,4,4,4,5};//去除相邻重复元素
    auto it=unique(vec.begin(),vec.end());
    //unique操作以后vec变成了1,2,3,4,5,?,?,?（后面的值是任意的）
    //it指向2的位置（去重后的部分的下一个位置）
    vec.erase(it,vec.end());
    for(int i=0;i<vec.size();++i)cout<<vec[i]<<' ';
}