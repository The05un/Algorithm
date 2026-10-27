#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 3e6 + 5;
const int M = 510;
const int mod = 1e9 + 7;

//给定正整数 n,p，求 [1,n] 中所有整数在模 p 意义下的乘法逆元。

//a 模 p 的乘法逆元定义为 ax ≡ 1 (modp) 的解。

int n, p;
int inv[N];

void build(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (int)(p - (i64)inv[p % i] * (p / i) % p);
    }
}

void solve() {
    cin >> n >> p;
    build(n);
    for (int i = 1; i <= n; ++i) cout << inv[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}