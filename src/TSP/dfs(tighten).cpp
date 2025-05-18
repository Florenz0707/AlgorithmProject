#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：采用DFS递归搜索的写法，使用进一步的剪枝，能够正确求解
 * 问题：仅能解决n<=17规模的问题，最高用时150000ms左右
 */

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0x3f3f3f3f
#define MAXN 50

int n;
int grid[MAXN][MAXN];
int minn_grid[MAXN][MAXN];      // f[i][j]: shortest distance from 1 to i by j edges
int vis[MAXN];
int path[MAXN];
int minn = INF;
ll cnt = 0;

void getMinnGrid(int node, int dist, int len) {
    if (len >= n) return;
    for (int i = 2; i <= n; ++i) {
        if (i == node) continue;
        if (minn_grid[i][len + 1] == 0 || dist + grid[node][i] < minn_grid[i][len + 1]) {
            minn_grid[i][len + 1] = dist + grid[node][i];
            getMinnGrid(i, dist + grid[node][i], len + 1);
        }
    }
}

void dfs(int node, int cost, int len, int cur_path[]) {
    cnt += 1;
    if (len >= n) {
        if (grid[1][node] != 0 && cost + grid[1][node] < minn) {
            minn = cost + grid[1][node];
            for (int i = 1; i <= n; ++i) path[i] = cur_path[i];
        }
        return;
    }
    // if (cost >= minn) return;
    // tighten cut-branch condition
    if (cost + minn_grid[node][n - len + 1] >= minn) return;
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

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            minn_grid[i][j] = 0;
        }
    }
    getMinnGrid(1, 0, 0);

    int tmp_path[n + 2];
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    vis[1] = 1;
    tmp_path[1] = 1;
    dfs(1, 0, 1, tmp_path);

    long end = clock();
    cout << "Time cost: " << (double) (end - start) << " ms.\n";
    cout << "Recursive function called times: " << cnt << endl;
    cout << "Min cost: " << minn << endl;
    cout << "Path: ";
    for (int i = 1; i <= n; ++i) cout << path[i] << " ";
    cout << endl;

    return 0;
}