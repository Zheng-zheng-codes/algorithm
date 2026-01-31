#include<bits/stdc++.h>
using namespace std;
int Rand(int l,int r){
    return rand()%(r-l+1)+l;
}
int n,m,q;
int main(){
    system("g++ 1.cpp -o 1");
    time(0);
    int N=1000000;
    for(int P=1;P<=7;P++){
        string filein=string(1,P+'0')+".in";
        string fileout=string(1,P+'0')+".out";
        freopen(filein.c_str(),"w",stdout);
        cout<<N<<'\n'<<N<<'\n';
        for(int i=1;i<=N;i++){
            int l=Rand(1,N),r=Rand(1,N);
            if(l>r){
                swap(l,r);
            }
            cout<<l<<' '<<r<<'\n';
        }
        cout<<N<<'\n';
        for(int i=1;i<=N;i++){
            int l=Rand(1,N),r=Rand(1,N);
            if(l>r){
                swap(l,r);
            }
            cout<<l<<' '<<r<<'\n';
        }
        fclose(stdout);
        // 恢复 stdout (平台相关)
        #ifdef _WIN32
            freopen("CON", "w", stdout);
        #else
            freopen("/dev/tty", "w", stdout);
        #endif

        string s="1.exe < "+filein+" > "+fileout;
        system(s.c_str());
    }
    return 0;
}