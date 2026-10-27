#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e5 + 5;
const int M = 50;
const int mod = 1e9 + 7;

int t, m;
int w[N], v[N];
int dp[N];

void solve() {
    cin >> t >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> w[i] >> v[i];
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = t; j >= w[i]; --j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[t] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}