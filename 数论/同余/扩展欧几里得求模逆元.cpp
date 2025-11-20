#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
ll mod_inverse(ll a, ll p) {
    ll x, y;
    ll d = exgcd(a, p, x, y);
    if (d != 1) return -1; // 模逆元不存在
    else return (x % p + p) % p; // 保证是正数
}
int main() {
    ll a, mod;
    cin >> a >> mod;
    cout << mod_inverse(a, mod) << "\n";
    return 0;
}