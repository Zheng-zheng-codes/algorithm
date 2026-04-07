#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    vector<int>vec={1,2,3};
    while(next_permutation(vec.begin(),vec.end()))//把全排列按字典序输出
    //下一个全排列还存在返回true，并把vec换成下一个全排列
    //否则返回false，vec变成第一个全排列
    //对所有全排列不会去重
    {
        for(int num:vec)cout<<num<<' ';
        cout<<'\n';
    }
    //同理，还有prev_mutation
    vector<int>vec2={3,2,1};
    while(prev_permutation(vec2.begin(),vec2.end()))//把全排列按倒字典序输出
    //上一个全排列还存在返回true，并把vec2换上一个全排列
    //否则返回false，vec2变成最后一个全排列
    //对所有全排列不会去重
    {
        for(int num:vec2)cout<<num<<' ';
        cout<<'\n';
    }
}