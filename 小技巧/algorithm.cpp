#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> v = {12, 81, 37, 31, 4, 95, 64, 18, 79, 23, 12};
    // 1. 排序
    sort(v.begin(), v.end());  // 升序排序
    sort(v.begin(), v.end(), greater<int>());  // 降序排序
    // 2. 查找
    auto it = find(v.begin(), v.end(), 4);  // 查找元素 4
    if (it != v.end()) cout << "找到4" << "\n";  // 查找
    int cnt = count(v.begin(), v.end(), 12);  // 统计元素 12 的个数
    cout << "有 " << cnt << " 个 12" << "\n";
    // 3. 二分查找
    sort(v.begin(), v.end());  // 先排序
    if (binary_search(v.begin(), v.end(), 4)) cout << "找到4" << "\n";  // 二分查找
    auto it1 = upper_bound(v.begin(), v.end(), 31);  // 查找大于 31 的第一个元素
    cout << *it1 << "\n";
    cout << it1 - v.begin() << "\n";  // 返回下标
    auto it2 = lower_bound(v.begin(), v.end(), 31);  // 查找不小于 31 的第一个元素
    cout << *it2 << "\n";
    cout << it2 - v.begin() << "\n";  // 返回下标
    // 4. 反转
    reverse(v.begin(), v.end());  // 反转
    // 5. 集体操作
    transform(v.begin(), v.end(), v.begin(), [](int x) { return x + 1; });  // 所有元素加 1
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });  // 输出结果
    cout << "\n";
    replace(v.begin(), v.end(), 5, 10);  // 将所有 5 替换为 10
    replace_if(v.begin(), v.end(), [](int x) { return x > 50; }, 0);  // 将大于 50 的数替换为 0
    int sum = accumulate(v.begin(), v.end(), 0);  // 累加容器元素
    cout << "sum = " << sum << "\n";
    // 6. 拷贝
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2(3);  // 创建一个大小为 3 的空容器
    copy(v1.begin(), v1.begin() + 3, v2.begin());  // 复制 v1 的前 3 个元素到 v2
    // 7. 移除
    auto new_end = remove(v.begin(), v.end(), 0);  // 移除所有 0
    v.erase(new_end, v.end());  // 使用 erase 调整容器大小
    remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });  // 移除所有偶数
    v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());  // 使用 erase 移除偶数
    return 0;
}
