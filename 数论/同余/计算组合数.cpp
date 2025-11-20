#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5; // 记得根据题目需要调整大小
const int MOD = 1e9 + 7; // 模数，通常是质数

ll fact[N], invFact[N];

// 计算 x^y % p 的快速幂
ll qpow(ll x, ll y, ll p) {
    ll res = 1;
    x %= p;
    while (y) {
        if (y & 1) res = res * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return res;
}

// 预处理阶乘和阶乘逆元
void init_factorials(int n, int p) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % p;
    }
    invFact[n] = qpow(fact[n], p - 2, p); // 使用费马小定理求逆元
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = invFact[i + 1] * (i + 1) % p;
    }
}

// 求组合数 C(n, k) % p
ll comb(int n, int k, int p) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % p * invFact[n - k] % p;
}

int main() {
    int n, k;
    cin >> n >> k;
    init_factorials(n, MOD); // 预处理阶乘和逆元
    cout << comb(n, k, MOD) << endl;
    return 0;
}
