#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5; // 记得根据题目需要调整大小
const int MOD = 1e9 + 7; // 模数，通常是质数

ll inv[N];

// 预处理 1~n 的所有逆元
void init_inv(int n, int p) {
    inv[1] = 1; // 特判
    for (int i = 2; i <= n; i++) {
        inv[i] = (p - p/i) * inv[p%i] % p;
    }
}
