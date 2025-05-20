#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：采用MST最小生成树的贪心策略，基础：数据集以欧式距离为边权，满足三角不等式，可以贪心求近似解
 * 问题：可以解决任意规模的问题，但是有一定误差
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
int path[MAXN];
int minn = INF;

void solve(int st) {
    int vis[MAXN];
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    int mst[MAXN];
    int cnt = 0;

    vis[st] = 1;
    mst[++cnt] = st;

    while (cnt < n) {
        int next = 0, minx = INF;
        for (int i = 1; i <= cnt; ++i) {
            for (int k = 1; k <= n; ++k) {
                if (!vis[k] && grid[i][k] != 0 && grid[i][k] < minx) {
                    next = k;
                    minx = grid[i][k];
                }
            }
        }
        vis[next] = 1;
        mst[++cnt] = next;
    }

    int sum = 0;
    for (int i = 1; i <= n; ++i) sum += grid[mst[i]][mst[(i + 1) % n]];
    if (sum < minn) {
        minn = sum;
        for (int i = 1; i <= n; ++i) path[i] = mst[i];
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

    for (int i = 1; i <= n; ++i)
        solve(i);  // 最小生成树与起点选取有关

    long end = clock();
    cout << "Time cost: " << (double)(end - start) << " ms.\n";
    cout << "Min cost: " << minn << endl;
    for (int i = 1; i <= n; ++i) cout << path[i] << " ";
    cout << endl;

    return 0;
}
