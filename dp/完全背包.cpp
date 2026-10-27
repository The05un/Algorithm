#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e7 + 5;
const int M = 1e4 + 5;
const int mod = 1e9 + 7;

i64 T, m;
i64 v[M], t[M];
i64 dp[N];

void solve() {
    cin >> T >> m;
    for (i64 i = 1; i <= m; ++i) {
        cin >> t[i] >> v[i];
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = t[i]; j <= T; ++j) {
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
        }
    }
    cout << dp[T] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}