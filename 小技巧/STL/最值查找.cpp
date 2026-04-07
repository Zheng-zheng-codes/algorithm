#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    vector<int>vec={1,3,2,5,1,10,8,11};
    cout<<*(max_element(vec.begin(),vec.end()))<<'\n';//返回最大元素 O(n)
    cout<<*(min_element(vec.begin(),vec.end()))<<'\n';//返回最小元素 O(n)
    nth_element(vec.begin(),vec.begin()+3,vec.end());
    for(int i=0;i<vec.size();++i)cout<<vec[i]<<' ';//O(nlogk)
    //第3个值前面都比它小，后面都比它大
}