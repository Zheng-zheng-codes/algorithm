//得到每个数的最小质因数
#include<bits/stdc++.h>
using namespace std;
const int MAX = 5e6 + 10;
int spf[MAX];  
void sieve() {
    for (int i = 2; i < MAX; ++i) {
        if (spf[i] == 0) {
            for (int j = i; j < MAX; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}
