#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * TODO: 需要的数组空间太大，对现有数据集，只能解决n=400，c=1000000级别的问题。
 */

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0xefffffff
#define MAXN 402
#define MAXC 1000004

int f[MAXN][MAXC];
int p[MAXN], w[MAXN];

int n, c;

void knapsack() {
    // initialize f[n][]
    int yMax = min(w[n] - 1, c);
    for (int y = 0; y <= yMax; ++y) f[n][y] = 0;
    for (int y = w[n]; y <= c; ++y) f[n][y] = p[n];

    // eval f[i][y] for 1 < i < n
    for (int i = n - 1; i > 1; --i) {
        yMax = min(w[i] - 1, c);
        for (int y = 0; y <= yMax; ++y) {
            f[i][y] = f[i + 1][y];
        }
        for (int y = w[i]; y <= c; ++y) {
            f[i][y] = max(f[i + 1][y], f[i + 1][y - w[i]] + p[i]);
        }
    }

    // eval f[1][c]
    f[1][c] = f[2][c];
    if (c >= w[1]) f[1][c] = max(f[1][c], f[2][c - w[1]] + p[1]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int id;
        cin >> id >> p[i] >> w[i];
    }
    cin >> c;
    long start = clock();
    knapsack();
    long end = clock();
    cout << f[1][c] << endl;
    cout << "Time cost: " << (double)(end - start) << "ms\n";

    return 0;
}
