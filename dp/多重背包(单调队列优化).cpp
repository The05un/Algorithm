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
const int M = 100 + 5;
const int mod = 1e9 + 7;

int n, W;
int v[M], w[M], m[M];
int dp[2][N];
deque<int> dq;
int old = 0, nw = 1;

int ret_v(int i, int j) {
    return dp[old][j] - j / w[i] * v[i];
}

void solve() {
    cin >> n >> W;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i] >> m[i];
    }
    for (int i = 1; i <= n; ++i) {
        int md = w[i] - 1;
        if (i > 1) swap(nw, old);
        for (int k = 0; k <= min(W, md); ++k) {
            while (!dq.empty()) dq.pop_back();
            for (int j = k; j <= W; j += w[i]) {
                while (!dq.empty() && ret_v(i, j) >= ret_v(i, dq.back())) dq.pop_back();
                dq.push_back(j);
                while (!dq.empty() && j - dq.front() > m[i] * w[i]) dq.pop_front();
                dp[nw][j] = max(dp[old][j], ret_v(i, dq.front()) + j / w[i] * v[i]);
            }
        }
    }
    cout << dp[nw][W] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
