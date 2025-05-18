#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0xefffffff
#define MAXN 402

int n;
int cost[MAXN][MAXN];
int vis[MAXN];
int minn = 0;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> cost[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) vis[i] = 0;

    return 0;
}