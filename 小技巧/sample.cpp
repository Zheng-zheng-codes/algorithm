#include<bits/stdc++.h>
using namespace std;
int Rand(int l,int r){
    return rand()%(r-l+1)+l;
}
int main(){
    system("g++ std.cpp -o std");
    time(0);
    for(int P=1;P<=20;P++){
        string filein;
        string fileout;
        if(P/10){
            filein=string(1,P/10+'0')+string(1,P%10+'0')+".in";
            fileout=string(1,P/10+'0')+string(1,P%10+'0')+".out";

        }else{
            filein=string(1,P+'0')+".in";
            fileout=string(1,P+'0')+".out";
        }
        freopen(filein.c_str(),"w",stdout);
//-------------------------------------------------------------
        int n,w,k;
        n=5000,w=10000,k=Rand(0,n);
        cout<<n<<' '<<w<<' '<<k<<'\n';
        for(int i=1;i<=n;++i)
        {
            int W=Rand(1,w),v=Rand(1,1000000000);
            cout<<W<<' '<<v<<'\n';
        }
//-------------------------------------------------------------
        fclose(stdout);
        // 恢复 stdout (平台相关)
        #ifdef _WIN32
            freopen("CON", "w", stdout);
        #else
            freopen("/dev/tty", "w", stdout);
        #endif

        string s="./std < "+filein+" > "+fileout;//Linux系统
        //string s="std.exe < "+filein+" > "+fileout;//windowx系统
        cout<<filein<<" "<<fileout<<endl;
        system(s.c_str());
    }
    return 0;
}