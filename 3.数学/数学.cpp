#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    double PI=acos(-1);//π
    double a1=asin(0.5);//反正弦
    double a2=sin(PI);//正弦
    double b1=acos(0.5);//反余弦
    double b2=cos(PI);//余弦
    double c1=atan(0.5);//反正切
    double c2=tan(PI);//正切
    //余切、正割、余割没有
    double num1=exp(n);//e的n次方
    double num2=log(n);//以e为底n的对数
    double num3=sqrt(n);//开方
    int m;
    cin>>m;
    double num4=pow(n,m);//n的m次方
    double num5=log10(n);//以10为底n的对数
    double num6=log2(n);//以2为底n的对数
    return 0;
}