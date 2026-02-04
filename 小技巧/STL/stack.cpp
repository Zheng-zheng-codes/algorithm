#include<bits/stdc++.h>
using namespace std;
int main()
{
    stack<int> s;
    // 1. 入栈
    s.push(10);
    s.push(20);
    s.push(30);
    // 栈顶是 30
    cout << "栈顶元素：" << s.top() << endl;
    // 2. 出栈
    s.pop(); // 弹出 30
    cout << "新的栈顶：" << s.top() << endl; // 20
    // 3. 栈大小与判空
    cout << "栈大小：" << s.size() << endl;   // 2
    cout << (s.empty() ? "空" : "非空") << endl;
    return 0;
}