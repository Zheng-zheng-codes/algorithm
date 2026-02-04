#include<bits/stdc++.h>
using namespace std;
int main()
{
    map<string, int> m;
    // 插入方式 1：使用下标（如果 key 不存在，会创建并初始化为 0）
    m["apple"] = 3;
    m["banana"] = 5;
    // 插入方式 2：insert 函数
    m.insert({"orange", 2});
    // 访问
    cout << "apple 数量：" << m["apple"] << endl;
    // 判断 key 是否存在
    if (m.count("banana")) cout << "香蕉有货！" << endl;
    // 遍历
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " -> " << it->second << endl;
    }
    //反向遍历
    for (auto it = m.rbegin(); it != m.rend(); ++it) {
        cout << it->first << " -> " << it->second << endl;
    }
    // 删除键
    m.erase("banana");
    return 0; 
}