/*
Beerus 需要对一个包含 N 个整数的数组进行排序。但 Beerus 不擅长算法 —— 他擅长的是破坏！
他可以一次性销毁数组中所有“无序”的数字。
一个数字 A[i] 被认为是“有序”的，当且仅当它满足以下两个条件：
A[i] 是数组中的第一个元素，或者它不小于左边的元素（即 A[i] >= A[i-1]）；
A[i] 是数组中的最后一个元素，或者它不大于右边的元素（即 A[i] <= A[i+1]）。
否则，它会被 Beerus 一次性摧毁（删除）。
例如，对于数组 [1, 4, 5, 2, 3]：
数字 5 被删除，因为它比右边的 2 大；
数字 2 被删除，因为它比左边的 5 小；
删除之后得到新数组 [1, 4, 3]。
如果新数组中仍然存在“无序”的数字，Beerus 会继续进行破坏，直到整个数组变成“完全有序”。
请你帮 Beerus 预测最终剩下的数组。
*/
#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node* prv;
    node* nxt;
    bool alive;       // 标记节点是否还存在
    bool scheduled;   // 标记节点是否已被安排在待删队列中

    node() {
        prv = nullptr;
        nxt = nullptr;
        alive = true;
        scheduled = false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 0) {
            cout << 0 << "\n\n";
            continue;
        }

        // —— 1. 建立双向链表 —— 
        node* head = nullptr;
        node* temp = nullptr;

        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;

            if (i == 0) {
                head = new node();
                head->val = num;
                head->prv = nullptr;
                head->nxt = nullptr;
                head->alive = true;
                head->scheduled = false;
                temp = head;
            } else {
                node* tnode = new node();
                tnode->val = num;
                tnode->alive = true;
                tnode->scheduled = false;

                // 连接到前一个节点 temp
                tnode->prv = temp;
                tnode->nxt = nullptr;
                temp->nxt = tnode;

                // 更新 temp
                temp = tnode;
            }
        }

        // —— 2. 定义辅助函数：判断一个节点是否“无序”——
        auto is_unsorted = [&](node* cur) {
            if (!cur->alive) return false;

            // 看左边
            if (cur->prv && cur->prv->alive && cur->val < cur->prv->val) {
                return true;
            }
            // 看右边
            if (cur->nxt && cur->nxt->alive && cur->val > cur->nxt->val) {
                return true;
            }
            return false;
        };

        // —— 3. 把第一轮所有“无序”节点加入队列 —— 
        queue<node*> q;
        // 为了后面方便访问所有节点并释放内存，我们把所有节点都压到 vector 里
        vector<node*> all_nodes;
        all_nodes.reserve(n);
        for (node* p = head; p != nullptr; p = p->nxt) {
            all_nodes.push_back(p);
        }

        for (node* p : all_nodes) {
            if (is_unsorted(p)) {
                q.push(p);
                p->scheduled = true;
            }
        }

        // —— 4. 迭代删除 —— 
        while (!q.empty()) {
            int sz = q.size();
            // 这一轮所有要删的节点都先收集下来
            vector<node*> to_delete;
            to_delete.reserve(sz);
            for (int i = 0; i < sz; i++) {
                node* cur = q.front();
                q.pop();
                // 可能已经在前面轮次被删掉
                if (!cur->alive) continue;
                to_delete.push_back(cur);
            }

            // 收集受影响的邻居
            vector<node*> affected;
            affected.reserve(to_delete.size() * 2);
            for (node* cur : to_delete) {
                if (cur->prv && cur->prv->alive) {
                    affected.push_back(cur->prv);
                }
                if (cur->nxt && cur->nxt->alive) {
                    affected.push_back(cur->nxt);
                }
            }

            // 真正删除：从链表中剪掉，并标记 alive = false
            for (node* cur : to_delete) {
                cur->alive = false;
                if (cur->prv) {
                    cur->prv->nxt = cur->nxt;
                }
                if (cur->nxt) {
                    cur->nxt->prv = cur->prv;
                }
            }

            // 下一轮检查：仅对“受影响的邻居”做 is_unsorted
            for (node* nei : affected) {
                if (!nei->alive) continue;
                if (nei->scheduled) continue;
                if (is_unsorted(nei)) {
                    q.push(nei);
                    nei->scheduled = true;
                }
            }
        }

        // —— 5. 输出剩下的元素 —— 
        // 先定位新的 head（最左边第一个 alive 节点）
        node* newHead = head;
        while (newHead && !newHead->alive) {
            newHead = newHead->nxt;
        }

        vector<int> result;
        for (node* p = newHead; p != nullptr; p = p->nxt) {
            if (p->alive) {
                result.push_back(p->val);
            }
        }

        cout << result.size() << "\n";
        if (!result.empty()) {
            for (int i = 0; i < (int)result.size(); i++) {
                cout << result[i] << (i + 1 < (int)result.size() ? ' ' : '\n');
            }
        } else {
            cout << "\n";
        }

        // —— 6. 释放链表内存 —— 
        for (node* p : all_nodes) {
            delete p;
        }
    }

    return 0;
}
