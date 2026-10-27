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
const int M = 1000 + 5;
const int mod = 1e9 + 7;

int n, m;
int a[N];
int stmax[18][N];
int lg2[N];

void build(int n) {
	lg2[0] = -1;
	for (int i = 1; i <= n; ++i) {
		lg2[i] = lg2[i >> 1] + 1;
	}
	int k = lg2[n];
	for (int i = 1; i <= n; ++i) {
		stmax[0][i] = a[i];
	}
	for (int j = 1; j <= k; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			stmax[j][i] = max(stmax[j - 1][i], stmax[j - 1][i + (1 << (j - 1))]);
		}
	}
}

int query(int a, int b) {
	int len = lg2[b - a  + 1];
	int res = max(stmax[len][a], stmax[len][b - (1 << len) + 1]);
	return res;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(n);
    while (m--) {
    	int l, r;
    	cin >> l >> r;
    	cout << query(l, r) << "\n";
    }
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1; //cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
