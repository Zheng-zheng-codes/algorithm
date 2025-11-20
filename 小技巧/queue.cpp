#include<bits/stdc++.h>
using namespace std;
int main()
{
    queue<int>q;
    // 1. 入队
    q.push(10);
    q.push(20);
    q.push(30);
    // 2. 访问队头/队尾
    cout << "队头：" << q.front() << endl; // 10
    cout << "队尾：" << q.back() << endl;  // 30
    // 3. 出队（弹出队头）
    q.pop();  // 移除10
    cout << "新的队头：" << q.front() << endl; // 20
    // 4. 队列大小 & 判空
    cout << "队列大小：" << q.size() << endl;   // 2
    cout << (q.empty() ? "空" : "非空") << endl; // 非空
    return 0;
}