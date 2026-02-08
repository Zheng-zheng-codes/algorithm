#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;
int minp[MAXN];       // minp[x] 表示 x 的最小质因子
vector<int> primes;
// 欧拉筛
void Euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minp[i] || 1LL * i * p > n) break;
            minp[i * p] = p;
        }
    }
}