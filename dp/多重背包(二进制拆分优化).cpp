#include<bits/stdc++.h>
#include <pthread.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e5 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;

int n, W;
int v[M], w[M], m[M];
int dp[N];
int new_n;
int new_v[N], new_w[N];

void solve() {
    cin >> n >> W;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i] >> m[i];
    }
    int new_n = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m[i]; j <<= 1){
            m[i] -= j;
            new_v[++new_n] = j * v[i];
            new_w[new_n] = j * w[i];
        }
        if (m[i]) {
            new_v[++new_n] = m[i] * v[i];
            new_w[new_n] = m[i] * w[i];
        }
    }
    for (int i = 1; i <= new_n; ++i) {
        for (int j = W; j >= new_w[i]; --j) {
            dp[j] = max(dp[j], dp[j - new_w[i]] + new_v[i]);
        }
    }
    cout << dp[W] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}