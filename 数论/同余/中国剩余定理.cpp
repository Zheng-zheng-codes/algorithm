#include <iostream>
using namespace std;

typedef long long ll;

// 扩展欧几里得算法，求解 ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// 求解中国剩余定理
ll chinese_remainder(ll a[], ll m[], int k) {
    ll M = 1;
    for (int i = 0; i < k; i++) {
        M *= m[i];  // 计算所有模数的积
    }

    ll x = 0;
    for (int i = 0; i < k; i++) {
        ll Mi = M / m[i];
        ll yi, _; 
        exgcd(Mi, m[i], yi, _);  // 求Mi关于mi的逆元yi
        x = (x + a[i] * Mi * yi) % M;  // 计算解
    }
    return (x + M) % M;  // 保证解为正
}

int main() {
    int k = 3;
    ll a[] = {2, 3, 1};
    ll m[] = {3, 5, 7};
    
    cout << "The solution is: " << chinese_remainder(a, m, k) << endl;
    return 0;
}
