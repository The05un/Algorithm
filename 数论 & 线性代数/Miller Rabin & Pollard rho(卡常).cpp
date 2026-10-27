#include<bits/stdc++.h>
using namespace std;

using ll = long long;
ll max_factor = 1;

mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

ll mul_mod(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}
ll fast_pow(ll x, ll y, ll m) {
    ll res = 1;
    x %= m;
    while (y) {
        if (y & 1) res = mul_mod(res, x, m);
        x = mul_mod(x, x, m);
        y >>= 1;
    }
    return res;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
bool witness(ll a, ll n) {
    ll u = n - 1;
    ll t = 0;
    while ((u & 1) == 0) u = u >> 1, t++;
    ll x1, x2;
    x1 = fast_pow(a, u, n);
    for (int i = 1; i <= t; ++i) {
        x2 = mul_mod(x1, x1, n);
        if (x2 == 1 && x1 != 1 && x1 != n - 1) return 1;
        x1 = x2;
    }
    if (x1 != 1) return 1;
    return 0;
}
bool miller_rabin(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == p)
            return true;
        if (n % p == 0)
            return false;
    }
    ll base[] = {
        2, 325, 9375, 28178,
        450775, 9780504, 1795265022
    };
    for (ll a : base) {
        if (a % n == 0)
            continue;
        if (witness(a, n))
            return false;
    }
    return true;
}
ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    ll c = rng() % (n - 1) + 1;
    ll x = 0;
    ll y = 0;
    ll val = 1;
    for (ll k = 1; ; k <<= 1, y = x, val = 1) {
        for (ll i = 1; i <= k; ++i) {
            x = (mul_mod(x, x, n) + c) % n;
            val = mul_mod(
                val,
                x > y ? x - y : y - x,
                n
            );
            if (i % 127 == 0) {
                ll d = gcd(val, n);
                if (d > 1)
                    return d;
            }
        }
        ll d = gcd(val, n);
        if (d > 1)
            return d;
    }
}
void findfac(ll n) {
    if (n <= max_factor || n < 2)
        return;
    if (miller_rabin(n)) {
        max_factor = max(max_factor, n);
        return;
    }
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) {
            max_factor = max(max_factor, p);

            while (n % p == 0)
                n /= p;

            findfac(n);
            return;
        }
    }
    ll p = n;
    while (p == n)
        p = pollard_rho(n);
    while (n % p == 0)
        n /= p;
    findfac(p);
    findfac(n);
}

void solve() {
    max_factor = 1;
    ll n; cin >> n;
    if (miller_rabin(n)) cout << "Prime\n";
    else {
        findfac(n);
        cout << max_factor << "\n";
    }

}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}