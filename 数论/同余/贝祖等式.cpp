#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 扩展欧几里得算法，返回 gcd(a, b)，同时求出一组解 x, y 使得 ax + by = gcd
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; 
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x); // 注意 x 和 y 交换位置
    y -= (a / b) * x;
    return d;
}
// 解 ax + by = c 的函数
bool solve_bezout(ll a, ll b, ll c, ll &x, ll &y) {
    ll d = exgcd(a, b, x, y);
    if (c % d != 0) return false; // 无解
    x *= c / d;
    y *= c / d;
    return true; // 有解，x 和 y 已被赋值
}
int main() {
    ll a = 30, b = 18, c = 6;
    ll x, y;
    if (solve_bezout(a, b, c, x, y)) {
        cout << "Solution: x = " << x << ", y = " << y << "\n";
        // 验证：
        // 30 * x + 18 * y == 6
    } else {
        cout << "No solution.\n";
    }
    return 0;
}

