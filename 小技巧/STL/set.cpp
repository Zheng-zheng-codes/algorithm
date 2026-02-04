#include<bits/stdc++.h>
using namespace std;
int main()
{
    set<int> s;
    // 插入元素
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2); // 自动去重，不会插入重复值
    // 遍历
    for (int x : s) cout << x << " "; // 输出：2 5 8（自动升序）
    cout << endl;
    // 查找元素
    if (s.count(5)) cout << "找到5\n";
    //如果是multiset会查出有几个5
    // 删除元素
    s.erase(5); // 按值删除
    // 查找并删除（推荐写法）
    auto it = s.find(8);
    if (it != s.end()) s.erase(it);
    // 判断是否为空
    cout << (s.empty() ? "空" : "非空") << endl;
    return 0; 
}