#include <iostream>
#include <cmath>
using namespace std;

// 计算欧拉函数
int euler(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        // 如果 i 是 n 的因子
        if (n % i == 0) {
            // 将所有 i 的因子都除去
            while (n % i == 0) {
                n /= i;
            }
            // 更新欧拉函数的值
            result -= result / i;
        }
    }
    // 如果 n 大于 1，说明 n 是一个素数
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Euler's Totient Function of " << n << " is: " << euler(n) << endl;
    return 0;
}
