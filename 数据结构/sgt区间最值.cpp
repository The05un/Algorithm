#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = double;

const int N = 1e6 + 5;
const int M = 1000 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

i64 n, m;
i64 a[N];

struct sgt {
    i64 sum;
    i64 mx, sem;
    i64 cnt;
}tr[N << 2];

i64 ls(i64 p) { return p << 1; }
i64 rs(i64 p) { return p << 1 | 1; }

void push_up(i64 p) {
    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
    tr[p].mx = max(tr[ls(p)].mx, tr[rs(p)].mx);

    if (tr[ls(p)].mx > tr[rs(p)].mx) {
        tr[p].cnt = tr[ls(p)].cnt;
        tr[p].sem = max(tr[ls(p)].sem, tr[rs(p)].mx);
    } else if (tr[ls(p)].mx < tr[rs(p)].mx) {
        tr[p].cnt = tr[rs(p)].cnt;
        tr[p].sem = max(tr[rs(p)].sem, tr[ls(p)].mx);
    } else {
        tr[p].cnt = tr[ls(p)].cnt + tr[rs(p)].cnt;
        tr[p].sem = max(tr[rs(p)].sem, tr[ls(p)].sem);
    }
}

void lazy(i64 p, i64 v) {
    if (v < tr[p].mx) {
        tr[p].sum -= tr[p].cnt * (tr[p].mx - v);
        tr[p].mx = v;
    }
}

void push_down(i64 p) {
    lazy(ls(p), tr[p].mx);
    lazy(rs(p), tr[p].mx);
}

void build(i64 p, i64 pl, i64 pr) {
    if (pl == pr) {
        tr[p].mx = tr[p].sum = a[pl];
        tr[p].cnt = 1;
        tr[p].sem = LLONG_MIN;
        return;
    }
    i64 mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void setMin(i64 p, i64 pl, i64 pr, i64 L, i64 R, i64 x) {
    if (x >= tr[p].mx) {
        return;
    }
    if ((tr[p].sem < x || pl == pr) && L <= pl && pr <= R) {
        lazy(p, x);
        return;
    }
    push_down(p);
    i64 mid = (pl + pr) >> 1;
    if (L <= mid) setMin(ls(p), pl, mid, L, R, x);
    if (R > mid) setMin(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

i64 queryMax(i64 p, i64 pl, i64 pr, i64 L, i64 R) {
    if (L <= pl && pr <= R) {
        return tr[p].mx;
    }
    push_down(p);
    i64 mid = (pl + pr) >> 1;
    i64 res = LLONG_MIN;
    if (L <= mid) res = max(queryMax(ls(p), pl, mid, L, R), res);
    if (R > mid) res = max(queryMax(rs(p), mid + 1, pr, L, R), res);
    return res;
}

i64 querySum(i64 p, i64 pl, i64 pr, i64 L, i64 R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum;
    }
    push_down(p);
    i64 mid = (pl + pr) >> 1;
    i64 res = 0;
    if (L <= mid) res += querySum(ls(p), pl, mid, L, R);
    if (R > mid) res += querySum(rs(p), mid + 1, pr, L, R);
    return res;
}

void solve() {
    cin >> n >> m;
    for (i64 i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        i64 op;
        cin >> op;
        if (op == 0) {
            i64 x, y, t;
            cin >> x >> y >> t;
            setMin(1, 1, n, x, y, t);
        } else if (op == 1) {
            i64 x, y;
            cin >> x >> y;
            cout << queryMax(1, 1, n, x, y) << "\n";
        } else {
            i64 x, y;
            cin >> x >> y;
            cout << querySum(1, 1, n, x, y) << "\n";
        }
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