#include<bits/stdc++.h>
using namespace std;
int main()
{
    // 1. 定义
    list<int> l1;  // 创建一个空的整型 list
    list<int> l2(5, 10);  // 创建一个大小为 5，所有元素初始化为 10 的 list
    list<int> l3 = {1, 2, 3, 4};  // 用初始化列表创建一个 list
    // 2. 添加元素
    l1.push_back(1);  // 在末尾插入 1
    l1.push_front(0); // 在前面插入 0
    // 3. 访问元素
    cout << "第一个元素：" << l1.front() << endl;  // 访问第一个元素
    cout << "最后一个元素：" << l1.back() << endl; // 访问最后一个元素
    // 4. 删除元素
    l1.pop_back();  // 删除末尾元素
    l1.pop_front(); // 删除前面元素
    l1.clear();//清空双向链表
    list<int>l={0,1,1,6};
    l.remove(1);//删除所有1
    //5.遍历
    for(auto it=l2.begin();it!=l2.end();it++)cout<<*it<<" ";
    cout<<"\n";
    //6.插入和删除元素
    auto it=l3.begin();//it指向第一个元素
    advance(it,2);//it指向第三个位置的元素
    cout<<*it<<"\n";
    l3.insert(it,2);//第三个位置的元素插入2
    //插入后it指向插入的后一个元素
    l3.erase(it);//删除第四个元素
    //删除后it指向被删元素的下一个元素
    //7.其他
    l3.sort();//排序（升序）
    l3.sort(greater<int>());//排序（降序）
    l3.unique();//删除相邻的相同元素
    list<int>l4={5,8,9};
    l4.sort();
    l3.merge(l4);//合并l3和l4并排好序(排序后l4清空)
    //注：merge本身不会排序，必须保证l3和l4都是排好序的
    return 0;
}