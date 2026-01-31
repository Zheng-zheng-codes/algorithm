#include<bits/stdc++.h>
using namespace std;
signed main(){//Windows版本,不同点1：fc与diff，不同点2：有无.exe后缀
    system("g++ data.cpp -o data");
    system("g++ Untitled-1.cpp -o std");//这两行的文件名要改
    system("g++ Untitled-2.cpp -o baoli");//
    for(int i=1;i<=1e3;i++){
        system("data.exe > in.in");
        system("std.exe < in.in > std.out");
        system("baoli.exe < in.in > out.out");
        if(system("fc std.out out.out >nul"))break;//之前测试没有>nul会莫名其妙WA
        cout<<i<<" AC\n"<<flush;
    }
    cout<<"WA\n"<<flush;
    return 0;
}
signed main1(){//Linux系统版本,不同点1：fc与diff，不同点2：有无.exe后缀
    system("g++ data.cpp -o data");
    system("g++ std.cpp -o std");
    system("g++ baoli.cpp -o baoli");
    for(int i=1;i<=1e3;i++){
        system("./data > in.in");
        system("./std < in.in > std.out");
        system("./baoli < in.in > out.out");
        if(system("diff std.out out.out"))break;
        cout<<i<<" AC\n"<<flush;
        // cout.flush();
    }
    cout<<"WA\n"<<flush;
    // cout.flush();
    return 0;
}
/*
g++ duipai.cpp -o duipai
./duipai

g++ std.cpp -o std
type 1.in | ./std.exe > 1.out
*/