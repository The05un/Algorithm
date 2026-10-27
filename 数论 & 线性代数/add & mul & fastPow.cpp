#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

const int N = 2e5 + 5;
const i64 mod = 1e9 + 7;

i64 a, b;

i64 add(i64 a, i64 b) {
	return ((i128)a + b) % mod;
}

i64 mul(i64 a, i64 b) {
	return (i128)a * b % mod;
}

i64 fastPow(i64 a, i64 n) {
	i64 ans = 1;
	a %= mod;
	while (n) {
		if (n & 1) ans = mul(ans, a);
		a = mul(a, a);
		n >>= 1;
	}
	return ans;
}

void solve() {
	cin >> a >> b;
	i64 ans1 = add(a, b);
	i64 ans2 = mul(a, b);
	i64 ans3 = fastPow(a, b);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1; //cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}