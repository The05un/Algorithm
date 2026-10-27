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
const int M = 100;
const int mod = 1e9 + 7;

int n, m;
int v[M], w[M];
int fan[M], fol[M][2];
int kin[M];
int dp[N];


void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int q;
        cin >> v[i] >> w[i] >> q;
        w[i] *= v[i];
        if (q) {
            fol[q][fan[q]++] = i;
            kin[i] = 0;
        } else {
            kin[i] = 1;
        }
    }
    for (int i = 0; i <= n; ++i) dp[i] = 0; 
    for (int i = 1; i <= m; ++i){
        if (!kin[i]) continue;
        for (int j = n; j >= v[i]; --j) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            int fan1 = fol[i][0];
            int fan2 = fol[i][1];
            if (fan1 && j >= v[i] + v[fan1]) {
                dp[j] = max(dp[j], dp[j - v[i] - v[fan1]] + w[i] + w[fan1]);
            }
            if (fan2 && j >= v[i] + v[fan2]) {
                dp[j] = max(dp[j], dp[j - v[i] - v[fan2]] + w[i] + w[fan2]);
            }
            if (fan1 && fan2 && j >= v[i] + v[fan2] + v[fan1]) {
                dp[j] = max(dp[j], dp[j - v[i] - v[fan2] - v[fan1]] + w[i] + w[fan2] + w[fan1]);
            }
        }
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}