#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int fa[maxn];
void init(int n)
{
    for(int i=1;i<=n;i++)fa[i]=i;
}
int find(int n)
{
    while(fa[n]!=n)
    {
        fa[n]=find(fa[n]);
    }
    return fa[n];
}
void unit(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx!=fy)
    {
        fa[fx]=fy;
    }
}