#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 33;
const int M = N * N;
int a[N][N];
int num[N][N];
int mt[M][M];
int d1[4] = { 0, 0, -1, 1 };
int d2[4] = { 1, -1, 0, 0 };


void solve() {
    int n, m; cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            num[i][j] = ++cnt;
        }
    }
    int p = m * n;
    memset(mt, 0, sizeof(mt));
    for (int i = 1; i <= p; ++i) {
        mt[i][i] = 2;
        for (int k = 0; k <= 3; ++k) {
            if (((i - 1) / m) + 1 + d1[k] >= 1 && ((i - 1) / m) + 1 + d1[k] <= n){
                if (((i - 1) % m) + 1 + d2[k] >= 1 && ((i - 1) % m) + 1 + d2[k] <= m) {
                    mt[i][num[((i - 1) / m) + 1 + d1[k]][((i - 1) % m) + 1 + d2[k]]] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= p; ++i) {
        mt[i][p + 1] = (6 - a[((i - 1) / m) + 1][((i - 1) % m) + 1]) % 3;
    }
    for (int i = 1; i <= p; ++i) {
        int mx = i;
        for (int j = i + 1; j <= p; ++j) {
            if (mt[j][i] > mt[mx][i]) mx = j;
        } swap(mt[i], mt[mx]);
        if (mt[i][i] == 2) {
            for (int j = i; j <= p + 1; ++j) mt[i][j] = (mt[i][j] * 2) % 3;
        }
        for (int j = i + 1; j <= p; ++j) {
            ll tmp = (6 + mt[i][i] * mt[j][i]) % 3;
            for (int k = i; k <= p + 1; ++k) {
                mt[j][k] -= mt[i][k] * tmp;
                mt[j][k] = (6 + mt[j][k]) % 3;
            }
        }
    }
    for (int i = p - 1; i >= 1; --i) {
        for (int j = p; j > i; --j) {
            mt[i][p + 1] -= mt[i][j] * mt[j][p + 1];
            mt[i][p + 1] = (6 + mt[i][p + 1]) % 3;
        }
    }
    int sum = 0;
    for (int i = 1; i <= p; ++i) {
        sum += mt[i][p + 1];
    }
    cout << sum << "\n";
    for (int i = 1; i <= p; ++i) {
        while (mt[i][p + 1]) {
            cout << (i - 1) / m + 1 << " " << (i - 1) % m + 1 << "\n";
            mt[i][p + 1]--;
        }
    }
    /*for (int i = 1; i <= p; ++i) {
        for (int j = 1; j <= p + 1; ++j) {
            cout << mt[i][j] << " ";
        } cout << "\n";
    }*/
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}