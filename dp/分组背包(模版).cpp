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

const int N = 1000 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;

int m, n;
vector<int> num[M];
int w[N], v[N];
int dp[N];

void solve() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        w[i] = a; v[i] = b; num[c].push_back(i);
    }
    for (int i = 0; i < M; ++i) {
        if (!num[i].empty()) {
            for (int j = m; j >= 0; --j) {
                for (int k : num[i]) {
                    if (j >= w[k]) {
                        dp[j] = max(dp[j], dp[j - w[k]] + v[k]);
                    }
                }
            }
        }
    }
    cout << dp[m] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}