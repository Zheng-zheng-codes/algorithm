#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;
void print_i128(i128 x) 
{
    if (x == 0) { putchar('0'); return; }
    if (x < 0) { putchar('-'); x = -x; }
    char buf[64]; int p = 0;
    while (x > 0) 
    {
        int digit = (int)(x % 10);
        buf[p++] = '0' + digit;
        x /= 10;
    }
    while (p--) putchar(buf[p]);
}