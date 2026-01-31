#include<bits/stdc++.h>
using namespace std;
int Rand(int x,int y){ return x+rand()%(y-x+1); } 
int main(){
    srand(time(0));
    int t=Rand(2,10);
    cout<<t<<'\n';
    for(int i=1;i<=t;i++)cout<<Rand(0,1e9)<<' ';
    cout<<'\n';
    return 0;
}