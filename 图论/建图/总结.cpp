#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 点的最大数量
const int MAXN = 11;

// 边的最大数量（无向图需要 2 倍空间）
const int MAXM = 21;

// 邻接矩阵方式建图
int graph1[MAXN][MAXN];

// 邻接表方式建图
vector<vector<pair<int, int>>> graph2;

// 链式前向星方式建图
int head[MAXN];
int nextEdge[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

void build(int n) {
    // 邻接矩阵清空
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            graph1[i][j] = 0;

    // 邻接表清空
    graph2.clear();
    graph2.resize(n + 1); // 下标从1开始

    // 链式前向星清空
    cnt = 1;
    memset(head, 0, sizeof(head));
}

// 链式前向星加边
void addEdge(int u, int v, int w) {
    nextEdge[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 建立有向图（带权）
void directGraph(const vector<vector<int>>& edges) {
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph1[u][v] = w;
        graph2[u].emplace_back(v, w);
        addEdge(u, v, w);
    }
}

// 建立无向图（带权）
void undirectGraph(const vector<vector<int>>& edges) {
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph1[u][v] = graph1[v][u] = w;
        graph2[u].emplace_back(v, w);
        graph2[v].emplace_back(u, w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
}

// 遍历所有结构
void traversal(int n) {
    cout << "邻接矩阵遍历 :" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "邻接表遍历 :" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "(邻居、边权) : ";
        for (const auto& p : graph2[i]) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }

    cout << "链式前向星 :" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "(邻居、边权) : ";
        for (int ei = head[i]; ei > 0; ei = nextEdge[ei]) {
            cout << "(" << to[ei] << "," << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main() {
    // 示例1：有向图
    int n1 = 4;
    vector<vector<int>> edges1 = {
        {1, 3, 6}, {4, 3, 4}, {2, 4, 2},
        {1, 2, 7}, {2, 3, 5}, {3, 1, 1}
    };
    build(n1);
    directGraph(edges1);
    traversal(n1);
    cout << "==============================" << endl;

    // 示例2：无向图
    int n2 = 5;
    vector<vector<int>> edges2 = {
        {3, 5, 4}, {4, 1, 1}, {3, 4, 2},
        {5, 2, 4}, {2, 3, 7}, {1, 5, 5}, {4, 2, 6}
    };
    build(n2);
    undirectGraph(edges2);
    traversal(n2);

    return 0;
}
