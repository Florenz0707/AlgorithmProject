#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * 说明：通过滚动数组进行优化，使额外空间占用从O(n*c)优化到了O(c)，可以解决当前数据集所有规模的问题
 * 问题：平均运行时间为1000-2000ms，对于数据规模n=600，c=100000000级别的问题，运行时间高达80000+ms
 */

#define ll long long
#define ull unsigned long long
#define endl "\n"
#define max(x, y) ((x) > (y)) ? (x) : (y)
#define min(x, y) ((x) > (y)) ? (y) : (x)

#define INF 0xefffffff
#define MAXN 602
#define MAXC 100000002

int f[MAXC];
int p[MAXN], w[MAXN];

ll n, c;

void knapsack() {
    // initialize f[]
    for (ll i = 0; i <= c; ++i) f[i] = 0;

    // eval f[] through rolling
    for (int i = 1; i <= n; ++i) {
        for (ll y = c; y >= w[i]; --y) {
            f[y] = max(f[y], f[y - w[i]] + p[i]);
        }
    }
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
    cout << f[c] << endl;
    cout << "Time cost: " << (double)(end - start) << "ms\n";

    return 0;
}
