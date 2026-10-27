#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e7 + 5;
const int mod = 1e9 + 7;

struct DescartesTree {
    i64 arr;
    i64 ls, rs;
}tr[N];
i64 sta[N];

i64 n;

void build() {
    i64 top = 0;
    for (i64 i = 1; i <= n; ++i) {
        i64 pos = top;
        while (pos > 0 && tr[sta[pos]].arr > tr[i].arr) {
            pos--;
        }
        if (pos > 0) {
            tr[sta[pos]].rs = i;
        }
        if (pos < top) {
            tr[i].ls = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}


void solve() {
    cin >> n;
    for (i64 i = 1; i <= n; ++i) {
        cin >> tr[i].arr;
    }
    build();
    i64 ans1 = 0;
    i64 ans2 = 0;
    for (i64 i = 1; i <= n; ++i) {
        ans1 ^= (i * (tr[i].ls + 1));
        ans2 ^= (i * (tr[i].rs + 1));
    }
    cout << ans1 << " " << ans2 << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}