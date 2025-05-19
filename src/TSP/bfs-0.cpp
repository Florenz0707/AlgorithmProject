#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：采用BFS优先队列搜索的写法并使用初步约束，能够基本正确求解
 * 问题：仅能解决n<=5规模的问题，之后占用空间过大，内存溢出
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

struct Status {
    int node = 0;
    int cost = 0;
    int len = 0;
    int vis[MAXN]{};
    int cur_path[MAXN]{};

    Status() = default;

    Status(int node, int cost, int len, const int vis[], const int cur_path[]) {
        this->node = node;
        this->cost = cost;
        this->len = len;
        copy(vis, vis + MAXN, this->vis);
        copy(cur_path, cur_path + MAXN, this->cur_path);
    }
};

struct StatusCompare {
    bool operator()(Status &s1, Status &s2) {
        if (s1.cost == s2.cost) return s1.len < s2.len;
        return s1.cost > s2.cost;
    }
};

priority_queue<Status, vector<Status>, StatusCompare> qwq;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }
    long start = clock();

    int init_vis[MAXN], init_path[MAXN];
    for (int i = 1; i <= n; ++i) {
        init_vis[i] = 0;
        init_path[i] = 0;
    }
    init_vis[1] = 1;
    init_path[1] = 1;

    qwq.emplace(1, 0, 1, init_vis, init_path);
    while (!qwq.empty()) {
        Status cur = qwq.top();
        qwq.pop();
        if (cur.cost > minn) continue;
        if (cur.len >= n) {
            if (cur.cost + grid[1][cur.node] < minn) {
                minn = cur.cost + grid[1][cur.node];
                for (int i = 1; i <= n; ++i) path[i] = cur.cur_path[i];
            }
            continue;
        }
        for (int i = 1; i <= n; ++i) {
            if (!cur.vis[i] && grid[cur.node][i] != 0 && cur.cost < minn) {
                int tmp_vis[MAXN], tmp_path[MAXN];
                for (int k = 1; k <= n; ++k) {
                    tmp_vis[k] = cur.vis[k];
                    tmp_path[k] = cur.cur_path[k];
                }
                tmp_vis[i] = 1;
                tmp_path[cur.len + 1] = i;
                qwq.emplace(i, cur.cost + grid[cur.node][i], cur.len + 1, tmp_vis, tmp_path);
            }
        }
    }

    long end = clock();
    cout << "Time cost: " << (double)(end - start) << " ms.\n";
    cout << "Min cost: " << minn << endl;
    for (int i = 1; i <= n; ++i) cout << path[i] << " ";
    cout << endl;

    return 0;
}
