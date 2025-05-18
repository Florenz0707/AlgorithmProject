#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0x3f3f3f3f
#define MAXN 50

int n;
int grid[MAXN][MAXN];
int vis[MAXN];
int path[MAXN];
int minn = INF;

void dfs(int node, int cost, int len, int cur_path[]) {
    if (len >= n) {
        if (grid[1][node] != 0 && cost + grid[1][node] < minn) {
            minn = cost + grid[1][node];
            for (int i = 1; i <= n; ++i) path[i] = cur_path[i];
        }
        return;
    }
    if (cost >= minn) return;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && grid[node][i] != 0) {
            vis[i] = 1;
            cur_path[len + 1] = i;
            dfs(i, cost + grid[node][i], len + 1, cur_path);
            vis[i] = 0;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }
    long start = clock();

    int _path[n + 2];
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    vis[1] = 1;
    _path[1] = 1;
    dfs(1, 0, 1, _path);

    long end = clock();
    cout << "Time cost: " << (double)(end - start) << " ms.\n";
    cout << "Min cost: " << minn << endl;
    for (int i = 1; i <= n; ++i) cout << path[i] << " ";
    cout << endl;

    return 0;
}