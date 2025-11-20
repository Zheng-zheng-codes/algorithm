#include<bits/stdc++.h>
using namespace std;
const int N = 510;
int g[N][N]; // g[u][v] 表示边的权重；无边时用 INF
const int INF = 0x3f3f3f3f;
void init(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = (i == j ? 0 : INF);
}
void addEdge(int u, int v, int w) {
    g[u][v] = w;
    // 若是无向图，还需加：
    // g[v][u] = w;
}
