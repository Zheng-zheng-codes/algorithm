#include <iostream>
using namespace std;
typedef long long ll;

// 快速幂
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 求a在mod下的逆元（mod是质数）
ll modInverse(ll a, ll mod) {
    return qpow(a, mod - 2, mod);
}

int main() {
    ll a, mod;
    cin >> a >> mod;
    cout << modInverse(a, mod) << "\n";
    return 0;
}
