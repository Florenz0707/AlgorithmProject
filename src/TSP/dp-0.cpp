#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：采用状压DP，动态递推最短路径长度，求解完毕后反推路径，花费时间短
 * 问题：空间换时间，仅能解决n<=17规模的问题，再大无法分配内存
 */

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0x3f3f3f3f
#define MAXN 17
#define MAXM ((1 << (MAXN - 1)) + 2)

int n;
ll m;
int grid[MAXN][MAXN];
int dp[MAXN][MAXM];
vector<int> path;

void solve() {
    // initialize dp[i][0]
    for (int i = 0; i < n; ++i) dp[i][0] = grid[i][0];

    // solve dp[i][j], update column first
    for (int j = 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j] = INF;
            if (((j >> (i - 1)) & 1) == 1) continue;    // node i visited
            for (int k = 1; k < n; ++k) {
                if (((j >> (k - 1)) & 1) == 0) continue;
                dp[i][j] = min(dp[i][j], grid[i][k] + dp[k][j ^ (1 << (k - 1))]);
            }
        }
    }
}

bool visDone(const int vis[]) {
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) return false;
    }
    return true;
}

void getPath() {
    int vis[MAXN];
    for (int i = 0; i < n; ++i) vis[i] = 0;
    vis[0] = 1;
    int pioneer = 0, minx = INF, tmp;
    ll S = m - 1;
    path.push_back(0);
    while (!visDone(vis)) {
        for (int i = 1; i < n; ++i) {
            if (!vis[i] && (S & (1 << (i - 1))) != 0) {
                if (minx > grid[i][pioneer] + dp[i][S ^ (1 << (i - 1))]) {
                    minx = grid[i][pioneer] + dp[i][S ^ (1 << (i - 1))];
                    tmp = i;
                }
            }
        }
        pioneer = tmp;
        path.push_back(pioneer);
        vis[pioneer] = 1;
        S = S ^ (1 << (pioneer - 1));
        minx = INF;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    long start = clock();

    m = 1 << (n - 1);
    solve();
    getPath();

    long end = clock();
    cout << "Time cost: " << (double) (end - start) << " ms.\n";
    cout << "Min cost: " << dp[0][m - 1] << endl;
    for (int &i : path) cout << i + 1 << " ";
    cout << endl;

    return 0;
}
