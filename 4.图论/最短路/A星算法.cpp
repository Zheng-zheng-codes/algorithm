#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
const int dx[4] = {-1, 1, 0, 0}; // up, down, left, right
const int dy[4] = {0, 0, -1, 1};

int manhattan(int x, int y, int tx, int ty) {
    return abs(tx - x) + abs(ty - y);
}

int minDistanceDijkstra(vector<vector<int>>& grid, int sx, int sy, int tx, int ty) {
    if (grid[sx][sy] == 0 || grid[tx][ty] == 0) return -1;
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    dist[sx][sy] = 1;
    pq.emplace(1, sx, sy);

    while (!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        if (x == tx && y == ty) return d;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                if (d + 1 < dist[nx][ny]) {
                    dist[nx][ny] = d + 1;
                    pq.emplace(d + 1, nx, ny);
                }
            }
        }
    }
    return -1;
}

int minDistanceAStar(vector<vector<int>>& grid, int sx, int sy, int tx, int ty) {
    if (grid[sx][sy] == 0 || grid[tx][ty] == 0) return -1;
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    dist[sx][sy] = 1;
    pq.emplace(1 + manhattan(sx, sy, tx, ty), sx, sy);

    while (!pq.empty()) {
        auto [f, x, y] = pq.top(); pq.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        if (x == tx && y == ty) return dist[x][y];
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                if (dist[x][y] + 1 < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    pq.emplace(dist[nx][ny] + manhattan(nx, ny, tx, ty), nx, ny);
                }
            }
        }
    }
    return -1;
}

vector<vector<int>> randomGrid(int n) {
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            grid[i][j] = (rand() % 100 < 30) ? 0 : 1;
    return grid;
}

int main() {
    srand(time(0));
    int len = 100;
    int testTime = 10000;
    cout << "Functional test begin\n";
    for (int i = 0; i < testTime; ++i) {
        int n = rand() % len + 2;
        auto grid = randomGrid(n);
        int sx = rand() % n, sy = rand() % n;
        int tx = rand() % n, ty = rand() % n;
        int ans1 = minDistanceDijkstra(grid, sx, sy, tx, ty);
        int ans2 = minDistanceAStar(grid, sx, sy, tx, ty);
        if (ans1 != ans2) {
            cout << "Mismatch found!\n";
            return 1;
        }
    }
    cout << "Functional test finished\n";

    cout << "Performance test begin\n";
    int N = 4000;
    auto grid = randomGrid(N);
    int sx = 0, sy = 0, tx = 3900, ty = 3900;

    auto start = chrono::steady_clock::now();
    int res1 = minDistanceDijkstra(grid, sx, sy, tx, ty);
    auto end = chrono::steady_clock::now();
    cout << "Dijkstra result: " << res1 << ", Time(ms): "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "\n";

    start = chrono::steady_clock::now();
    int res2 = minDistanceAStar(grid, sx, sy, tx, ty);
    end = chrono::steady_clock::now();
    cout << "A* result: " << res2 << ", Time(ms): "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "\n";
    cout << "Performance test finished\n";

    return 0;
}
