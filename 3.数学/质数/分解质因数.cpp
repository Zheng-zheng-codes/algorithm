#include<bits/stdc++.h>
using namespace std;
// 分解质因数（只输出不重复的质因子）
vector<int> getPrimeFactors(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}