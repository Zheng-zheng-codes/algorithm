#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
vector<int>tu[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int x,y;cin>>x>>y;
        tu[x].push_back(y);
        tu[y].push_back(x);
    }
    
}