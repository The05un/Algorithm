#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 2e5 + 5;

int n;

int lowbit(int x) { return x & (-x); }

int f(int limit, int col, int left, int right) {
	if (col == limit) return 1;
	int ban = col | left | right;
	int candidate = limit & (~ban);
	int place = 0;
	int ans = 0;
	while (candidate != 0) {
		place = lowbit(candidate);
		candidate ^= place;
		ans += f(limit, col | place, (left | place) >> 1, (right | place) << 1);
	}
	return ans;
}

int n_queens(int n) {
	if (n < 1) return 0;
	int limit = (1 << n) - 1;
	return f(limit, 0, 0, 0);
}


void solve() {
	cin >> n;
    int ans = n_queens(n);
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