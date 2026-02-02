#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<pair<int, int>> adj[N]; // adj[u] 存储 {v, w}

void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    // 若是无向图，还需加：
    // adj[v].push_back({u, w});
}
