#include<bits/stdc++.h>
using namespace std;
int main()
{
    deque<int> dq;
    // 插入元素
    dq.push_back(10);  // 尾部插入
    dq.push_front(5);  // 头部插入
    // 访问元素
    cout << "前端：" << dq.front() << endl; // 5
    cout << "后端：" << dq.back() << endl;  // 10
    // 删除元素
    dq.pop_front();  // 删除头部（5）
    dq.pop_back();   // 删除尾部（10）
    // 插入多个元素
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    // 随机访问
    cout << "中间元素：" << dq[1] << endl; // 2
    // 遍历
    for (int x : dq) cout << x << " "; // 输出：1 2 3
    return 0;
}