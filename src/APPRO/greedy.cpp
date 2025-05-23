#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：使用简单的贪心算法，总是选择和当前节点距离最近的节点
 * 问题：可以快速求解任意规模的问题，为近似解
 */

#define DEBUG
#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0x3f3f3f3f
#define MAXN 50

int n;
int grid[MAXN][MAXN];
int path[MAXN];
int minn = INF;

void solve(int st) {
    int vis[MAXN], _path[MAXN];
    int node = st;
    int cnt = 0;
    int cost = 0;
    fill(vis, vis + MAXN, 0);
    vis[node] = 1;
    _path[++cnt] = node;

    while (cnt < n) {
        int nxt, minx = INF;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && grid[node][i] < minx) {
                minx = grid[node][i];
                nxt = i;
            }
        }
        cost += minx;
        vis[nxt] = 1;
        _path[++cnt] = nxt;
        node = nxt;
    }

    cost += grid[node][st];
    if (cost < minn) {
        minn = cost;
        for (int i = 1; i <= n; ++i) path[i] = _path[i];
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

    for (int i = 1; i <= n; ++i) solve(i);

    long end = clock();
    cout << "Time cost: " << (double) (end - start) << " ms.\n";
    cout << "Min cost: " << minn << endl;
    for (int i = 1; i <= n; ++i) cout << path[i] << " ";
    cout << endl;

    return 0;
}

