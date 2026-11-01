#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = double;

const int N = 5e5 + 5;
const int M = 1000 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

i64 n, m;
i64 a[N];

struct sgt {
    i64 sum;
    i64 maxv, sem;
    i64 cnt;
    i64 maxAdd, otherAdd;

    i64 maxHistory;
    i64 maxAddtop;
    i64 otherAddtop;
}tr[N << 2];

i64 ls(i64 p) { return p << 1; }
i64 rs(i64 p) { return p << 1 | 1; }

void push_up(i64 p) {
    tr[p].maxHistory = max(tr[ls(p)].maxHistory, tr[rs(p)].maxHistory);

    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
    tr[p].maxv = max(tr[ls(p)].maxv, tr[rs(p)].maxv);

    if (tr[ls(p)].maxv > tr[rs(p)].maxv) {
        tr[p].cnt = tr[ls(p)].cnt;
        tr[p].sem = max(tr[ls(p)].sem, tr[rs(p)].maxv);
    } else if (tr[ls(p)].maxv < tr[rs(p)].maxv) {
        tr[p].cnt = tr[rs(p)].cnt;
        tr[p].sem = max(tr[ls(p)].maxv, tr[rs(p)].sem);
    } else {
        tr[p].cnt = tr[ls(p)].cnt + tr[rs(p)].cnt;
        tr[p].sem = max(tr[ls(p)].sem, tr[rs(p)].sem);
    }
}

void lazy(i64 p, i64 n, i64 maxAddv, i64 otherAddv, i64 maxUpv, i64 otherUpv) {
    tr[p].maxHistory = max(tr[p].maxHistory, tr[p].maxv + maxUpv);
    tr[p].maxAddtop = max(tr[p].maxAddtop, tr[p].maxAdd + maxUpv);
    tr[p].otherAddtop = max(tr[p].otherAddtop, tr[p].otherAdd + otherUpv);

    tr[p].sum += maxAddv * tr[p].cnt + otherAddv * (n - tr[p].cnt);
    tr[p].maxv += maxAddv;
    tr[p].sem += tr[p].sem == LLONG_MIN ? 0 : otherAddv;
    tr[p].maxAdd += maxAddv;
    tr[p].otherAdd += otherAddv;
}

void push_down(i64 p, i64 ln, i64 rn) {
    i64 tmp = max(tr[ls(p)].maxv, tr[rs(p)].maxv);
    if (tr[ls(p)].maxv == tmp) {
        lazy(ls(p), ln, tr[p].maxAdd, tr[p].otherAdd, tr[p].maxAddtop, tr[p].otherAddtop);
    } else {
        lazy(ls(p), ln, tr[p].otherAdd, tr[p].otherAdd, tr[p].otherAddtop, tr[p].otherAddtop);
    }
    if (tr[rs(p)].maxv == tmp) {
        lazy(rs(p), rn, tr[p].maxAdd, tr[p].otherAdd, tr[p].maxAddtop, tr[p].otherAddtop);
    } else {
        lazy(rs(p), rn, tr[p].otherAdd, tr[p].otherAdd, tr[p].otherAddtop, tr[p].otherAddtop);
    }
    tr[p].maxAdd = tr[p].otherAdd = tr[p].maxAddtop = tr[p].otherAddtop = 0;
}

void build(i64 p, i64 pl, i64 pr) {
    tr[p].maxAdd = tr[p].otherAdd = tr[p].maxAddtop = tr[p].otherAddtop = 0;
    if (pl == pr) {
        tr[p].sum = tr[p].maxv = tr[p].maxHistory = a[pl];
        tr[p].sem = LLONG_MIN;
        tr[p].cnt = 1;
        return;
    }
    i64 mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void add(i64 p, i64 pl, i64 pr, i64 L, i64 R, i64 x) {
    if (L <= pl && pr <= R) {
        lazy(p, pr - pl + 1, x, x, x, x);
        return;
    }
    i64 mid = (pl + pr) >> 1;
    push_down(p, mid - pl + 1, pr - mid);
    if (L <= mid) add(ls(p), pl, mid, L, R, x);
    if (R > mid) add(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

void setMin(i64 p, i64 pl, i64 pr, i64 L, i64 R, i64 x) {
    if (x >= tr[p].maxv) {
        return;
    }
    if (L <= pl && pr <= R && (tr[p].sem < x || pl == pr)) {
        lazy(p, pr - pl + 1, x - tr[p].maxv, 0, x - tr[p].maxv, 0);
        return;
    }
    i64 mid = (pl + pr) >> 1;
    push_down(p, mid - pl + 1, pr - mid);
    if (L <= mid) setMin(ls(p), pl, mid, L, R, x);
    if (R > mid) setMin(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

i64 querySum(i64 p, i64 pl, i64 pr, i64 L, i64 R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum;
    }
    i64 mid = (pl + pr) >> 1;
    push_down(p, mid - pl + 1, pr - mid);
    i64 res = 0;
    if (L <= mid) res += querySum(ls(p), pl, mid, L, R);
    if (R > mid) res += querySum(rs(p), mid + 1, pr, L, R);
    return res;
}

i64 queryMax(i64 p, i64 pl, i64 pr, i64 L, i64 R) {
    if (L <= pl && pr <= R) {
        return tr[p].maxv;
    }
    i64 mid = (pl + pr) >> 1;
    push_down(p, mid - pl + 1, pr - mid);
    i64 res = LLONG_MIN;
    if (L <= mid) res = max(res, queryMax(ls(p), pl, mid, L, R));
    if (R > mid) res = max(res, queryMax(rs(p), mid + 1, pr, L, R));
    return res;
}

i64 queryHistoryMax(i64 p, i64 pl, i64 pr, i64 L, i64 R) {
    if (L <= pl && pr <= R) {
        return tr[p].maxHistory;
    }
    i64 mid = (pl + pr) >> 1;
    push_down(p, mid - pl + 1, pr - mid);
    i64 res = LLONG_MIN;
    if (L <= mid) res = max(res, queryHistoryMax(ls(p), pl, mid, L, R));
    if (R > mid) res = max(res, queryHistoryMax(rs(p), mid + 1, pr, L, R));
    return res;
}



void solve() {
    cin >> n >> m;
    for (i64 i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b, k;
            cin >> a >> b >> k;
            add(1, 1, n, a, b, k);
        } else if (op == 2) {
            int a, b, v;
            cin >> a >> b >> v;
            setMin(1, 1, n, a, b, v);
        } else if (op == 3) {
            int a, b;
            cin >> a >> b;
            cout << querySum(1, 1, n, a, b) << "\n";
        } else if (op == 4) {
            int a, b;
            cin >> a >> b;
            cout << queryMax(1, 1, n, a, b) << "\n";
        } else {
            int a, b;
            cin >> a >> b;
            cout << queryHistoryMax(1, 1, n, a, b) << "\n";
        }
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