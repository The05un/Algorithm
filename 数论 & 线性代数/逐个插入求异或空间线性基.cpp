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
const int M = 2000 + 5;
const int mod = 1e9 + 7;

i64 n;
i64 p[64];
bool zero = 0;

void inSert(i64 x) {
    for (i64 i = 51; i >= 0; --i) {
        if (x >> i == 1) {
            if (p[i] == 0) {
                p[i] = x;
                break;
            } else {
                x ^= p[i];
            }
        }
    }
    if (x == 0) zero = 1;
}

void solve() {
    cin >> n;
    for (i64 i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        inSert(x);
    }
    i64 ans = 0;
    for (i64 i = 51; i >= 0; --i) {
        ans = max(ans, ans ^ p[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}