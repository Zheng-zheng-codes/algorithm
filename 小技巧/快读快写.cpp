//使用快读快写的时候不能关闭同步流
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x(0);bool f(0);char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar()) f^=ch=='-';
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
    return f?x=-x:x;
}
inline void write(int x){
    x<0?x=-x,putchar('-'):0;static short Sta[50],top(0);
    do{Sta[++top]=x%10;x/=10;}while(x);
    while(top) putchar(Sta[top--]|48);
    putchar('\n');
}