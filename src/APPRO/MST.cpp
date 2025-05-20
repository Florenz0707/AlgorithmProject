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

void getPath(int node, vector<int> &ret, vector<int> mst[]);

int n;
int grid[MAXN][MAXN];
int path[MAXN];
int minn = INF;

void solve(int st) {
    int vis[MAXN];
    vector<int> mst[MAXN];
    vector<int> ret;
    int cnt = 1;
    int sum = 0;

    for (int & i : vis) i = 0;
    vis[st] = 1;

    while (cnt < n) {
        int src = 0, dst = 0, minx = INF;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) continue;
            for (int k = 1; k <= n; ++k) {
                if (!vis[k] && grid[i][k] < minx) {
                    src = i;
                    dst = k;
                    minx = grid[i][k];
                }
            }
        }
        vis[dst] = 1;
        mst[src].push_back(dst);
        cnt++;
    }

    getPath(st, ret, mst);
    for (int i = 0; i < n; ++i) sum += grid[ret[i]][ret[(i + 1) % n]];
    if (sum < minn) {
        minn = sum;
        for (int i = 1; i <= n; ++i) path[i] = ret[i - 1];
    }
}

void getPath(int node, vector<int> &ret, vector<int> mst[]) {
    ret.push_back(node);
    for (int &nxt : mst[node]) getPath(nxt, ret, mst);
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
