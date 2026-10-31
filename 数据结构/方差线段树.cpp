#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = double;

const int N = 1e5 + 5;
const int M = 1000 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

int n, m;
f64 a[N];

struct node {
    f64 sum1;
    f64 sum2;
    f64 tag;
}tr[N << 2];

int ls(int p) { return p << 1; };
int rs(int p) { return p << 1 | 1; }

void push_up(int p) {
    tr[p].sum1 = tr[ls(p)].sum1 + tr[rs(p)].sum1;
    tr[p].sum2 = tr[ls(p)].sum2 + tr[rs(p)].sum2;
}

void build(int p, int pl, int pr) {
    tr[p].tag = 0;
    if (pl == pr) {
        tr[p].sum1 = a[pl];
        tr[p].sum2 = a[pl] * a[pl];
        return;
    }
    int mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addtag(int p, int pl, int pr, f64 x) {
    tr[p].sum2 += 2.0 * x * tr[p].sum1 + (f64)(pr - pl + 1) * x * x;
    tr[p].sum1 += (f64)(pr - pl + 1) * x;
    tr[p].tag  += x;
}

void push_down(int p, int pl, int pr) {
    if (pl == pr) return;
    if (tr[p].tag != 0.0) {
        int mid = (pl + pr) >> 1;
        addtag(ls(p), pl, mid, tr[p].tag);
        addtag(rs(p), mid + 1, pr, tr[p].tag);
        tr[p].tag = 0;
    }
}

void update(int p, int pl, int pr, int L, int R, f64 k) {
    if (L <= pl && pr <= R) {
        addtag(p, pl, pr, k);
        return;
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    if (L <= mid) update(ls(p), pl, mid, L, R, k);
    if (R > mid) update(rs(p), mid + 1, pr, L, R, k);
    push_up(p);
}

f64 query1(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum1;
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    f64 res = 0;
    if (L <= mid) res += query1(ls(p), pl, mid, L, R);
    if (R > mid) res += query1(rs(p), mid + 1, pr, L, R);
    return res;
}

f64 query2(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum2;
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    f64 res = 0;
    if (L <= mid) res += query2(ls(p), pl, mid, L, R);
    if (R > mid) res += query2(rs(p), mid + 1, pr, L, R);
    return res;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            f64 k;
            cin >> a >> b >> k;
            update(1, 1, n, a, b, k);
        } else if (op == 2) {
            int a, b;
            cin >> a >> b;
            f64 ans = query1(1, 1, n, a, b) / (f64)(b - a + 1);
            printf("%.4lf\n", ans);
        } else {
            int a, b;
            cin >> a >> b;
            f64 s1 = query1(1, 1, n, a, b);
            f64 ave = s1 / (b - a + 1);
            f64 ans = ave * ave + (query2(1, 1, n, a, b) - 2 * ave * s1) / (f64)(b - a + 1);
            printf("%.4lf\n", ans);
        }
    }
}

int main() {
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}