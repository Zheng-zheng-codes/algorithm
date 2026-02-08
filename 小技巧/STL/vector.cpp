#include<bits/stdc++.h>
using namespace std;
int main()
{
    //1.定义
    vector<int> v1;  // 创建一个空的整型vector
    vector<int> v2(5, 10);  // 创建一个大小为5，所有元素初始化为10的vector
    vector<int> v3 = {1, 2, 3, 4};  // 用初始化列表创建一个vector
    //2.添加元素
    v1.push_back(1);
    v2.insert(v2.begin()+2,5);//下标为2的数是5
    //3.访问数组
    cout << "第一个元素：" << v2[0] << endl;   // 通过下标访问
    cout << "第二个元素：" << v2.at(1) << endl; // 使用 at() 访问，支持越界检查
    cout << "第一个元素：" << v2.front() << endl;//访问第一个元素
    cout << "最后一个元素：" << v2.back() << endl; // 访问最后一个元素
    //4.获取大小
    cout << "vector 大小：" << v2.size() << endl;  // 获取元素个数
    cout << "最大容量：" << v2.capacity() << endl; // 获取当前分配的最大容量
    //不断插入数据时vector会扩容capacity就是扩容后的大小
    //5.删除元素
    v2.pop_back(); // 删除最后一个元素
    v2.erase(v2.begin()+2);//删掉下标为2的数
    v3.clear();    // 清空所有元素
    //6.遍历
    for(int i=0;i<v2.size();i++)cout<<v2[i]<<" ";
    cout<<"\n";
    for (auto it = v2.rbegin(); it != v2.rend(); ++it)cout << *it << " ";  // 输出：5 4 3 2 1
    cout << "\n";//反向遍历
    //7.其他
    v2.resize(10, 5);  // 将 vector 的大小扩展到 10，缺少的元素用 5 填充
    //如果大于10个元素，多余部分删掉
    vector<int>v=move(v2);//v2给v，v2清空
    v.assign(5, 10);  // 将 5 个元素 10 赋给 v
    //注：resize是改变大小，多删少补，assign是给数组清空后重新赋值
    return 0;
}