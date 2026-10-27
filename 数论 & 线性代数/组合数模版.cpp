#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int n;
ll fac[N];
ll inv[N];

ll fastPow(ll a, ll b) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

void init() {
    fac[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = (fac[i - 1] * i) % mod;
    inv[N - 1] = fastPow(fac[N - 1], mod - 2);
    for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
}

ll C(int n, int m) {
    if (m < 0 || m > n) return 0; //按题意添加
    return (fac[n] * inv[m] % mod * inv[n - m] % mod) % mod;
}

void solve() {
    cin >> n;
    while (n--) {
        ll a, b;
        cin >> a >> b;
        cout << C(a, b) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}