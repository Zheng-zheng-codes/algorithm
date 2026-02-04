#include<bits/stdc++.h>
using namespace std;
int main()
{
    int arr[10];
    memset(arr,0,sizeof(arr));//初始化数组
    string s="abc";
    ostringstream oss;//把数据输出到字符串
    oss<<"hello"<<" world"<<"\n";
    cout<<oss.str();
    string input = "123 4.56 Bob";
    istringstream iss(input);
    int n;
    double m;
    string name;
    iss>>n>>m>>name;
    cout<<n<<" "<<m<<" "<<name;
    return 0;
}