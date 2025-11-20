#include<bits/stdc++.h>
using namespace std;
int main()
{
    priority_queue<int> pq;//默认是大顶堆
    pq.push(10);
    pq.push(5);
    pq.push(20);
    cout << "当前堆顶元素：" << pq.top() << endl; // 20，最大值
    pq.pop(); // 弹出最大值（20）
    cout << "新的堆顶：" << pq.top() << endl; // 10
    cout << "当前元素个数：" << pq.size() << endl;
    priority_queue<int,vector<int>,greater<int>>minheap;//小顶堆
    return 0;
}