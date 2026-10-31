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
int a[N];

struct sgt {
    int sum, len;
    int mx1;
    int lmax1, rmax1;
    int mx0;
    int lmax0, rmax0;
    int tag;
}tr[N << 2];

struct node {
    int len;
    int mx;
    int lmx, rmx;
};

node merge(const node &a, const node& b) {
    node res;
    res.len = a.len + b.len;
    res.mx = max({a.mx, b.mx, a.rmx + b.lmx});
    res.lmx = a.lmx;
    if (a.lmx == a.len) res.lmx += b.lmx;
    res.rmx = b.rmx;
    if (b.rmx == b.len) res.rmx += a.rmx;
    return res;
}

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void push_up(int p) {
    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
    tr[p].len = tr[ls(p)].len + tr[rs(p)].len;

    tr[p].lmax1 = tr[ls(p)].lmax1;
    if (tr[ls(p)].lmax1 == tr[ls(p)].len) tr[p].lmax1 += tr[rs(p)].lmax1;

    tr[p].rmax1 = tr[rs(p)].rmax1;
    if (tr[rs(p)].rmax1 == tr[rs(p)].len) tr[p].rmax1 += tr[ls(p)].rmax1;

    tr[p].mx1 = max(tr[ls(p)].mx1, tr[rs(p)].mx1);
    tr[p].mx1 = max(tr[p].mx1, tr[ls(p)].rmax1 + tr[rs(p)].lmax1);

    tr[p].lmax0 = tr[ls(p)].lmax0;
    if (tr[ls(p)].lmax0 == tr[ls(p)].len) tr[p].lmax0 += tr[rs(p)].lmax0;

    tr[p].rmax0 = tr[rs(p)].rmax0;
    if (tr[rs(p)].rmax0 == tr[rs(p)].len) tr[p].rmax0 += tr[ls(p)].rmax0;

    tr[p].mx0 = max(tr[ls(p)].mx0, tr[rs(p)].mx0);
    tr[p].mx0 = max(tr[p].mx0, tr[ls(p)].rmax0 + tr[rs(p)].lmax0);
}

void build(int p, int pl, int pr) {
    tr[p].tag = -1;
    if (pl == pr) {
        tr[p].len = 1;
        tr[p].sum = a[pl];
        tr[p].lmax1 = a[pl];
        tr[p].rmax1 = a[pl];
        tr[p].mx1 = a[pl];
        tr[p].lmax0 = a[pl] ^ 1;
        tr[p].rmax0 = a[pl] ^ 1;
        tr[p].mx0 = a[pl] ^ 1;
        return;
    }
    int mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addtag(int p, int pl, int pr, int x) {
    if (x == 2) {
        if (tr[p].tag == 1 || tr[p].tag == 0) {
            tr[p].tag ^= 1;
        }
        if (tr[p].tag == 2) {
            tr[p].tag = -1;
        } else if (tr[p].tag == -1) {
            tr[p].tag = 2;
        }
        tr[p].sum = (pr - pl + 1) - tr[p].sum;
        int tmp1 = tr[p].lmax1;
        int tmp2 = tr[p].rmax1;
        int tmp3 = tr[p].mx1;
        tr[p].lmax1 = tr[p].lmax0;
        tr[p].rmax1 = tr[p].rmax0;
        tr[p].mx1 = tr[p].mx0;
        tr[p].lmax0 = tmp1;
        tr[p].rmax0 = tmp2;
        tr[p].mx0 = tmp3;
    } else if (x == 1) {
        tr[p].tag = 1;
        tr[p].sum = pr - pl + 1;
        tr[p].lmax1 = pr - pl + 1;
        tr[p].rmax1 = pr - pl + 1;
        tr[p].mx1 = pr - pl + 1;
        tr[p].lmax0 = 0;
        tr[p].rmax0 = 0;
        tr[p].mx0 = 0;
    } else {
        tr[p].tag = 0;
        tr[p].sum = 0;
        tr[p].lmax1 = 0;
        tr[p].rmax1 = 0;
        tr[p].mx1 = 0;
        tr[p].lmax0 = pr - pl + 1;
        tr[p].rmax0 = pr - pl + 1;
        tr[p].mx0 = pr - pl + 1;
    }
}

void push_down(int p, int pl, int pr) {
    if (tr[p].tag != -1) {
        int mid = (pl + pr) >> 1;
        addtag(ls(p), pl, mid, tr[p].tag);
        addtag(rs(p), mid + 1, pr, tr[p].tag);
        tr[p].tag = -1;
    }
}

void update(int p, int pl, int pr, int L, int R, int x) {
    if (L <= pl && pr <= R) {
        addtag(p, pl, pr, x);
        return;
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    if (L <= mid) update(ls(p), pl, mid, L, R, x);
    if (R > mid) update(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

int query1(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum;
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    int res = 0;
    if (L <= mid) res += query1(ls(p), pl, mid, L, R);
    if (R > mid) res += query1(rs(p), mid + 1, pr, L, R);
    return res;
}

node query2(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return {tr[p].len, tr[p].mx1, tr[p].lmax1, tr[p].rmax1};
    }
    push_down(p, pl, pr);
    int mid = (pl + pr) >> 1;
    if (L > mid) return query2(rs(p), mid + 1, pr, L, R);
    if (R <= mid) return query2(ls(p), pl, mid, L, R);
    node n1 = query2(ls(p), pl, mid, L, R);
    node n2 = query2(rs(p), mid + 1, pr, L, R);
    node res = merge(n1, n2);
    return res;
}



void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        l++; r++;
        if (op == 0) {
            update(1, 1, n, l, r, 0);
        } else if (op == 1) {
            update(1, 1, n, l, r, 1);
        } else if (op == 2) {
            update(1, 1, n, l, r, 2);
        } else if (op == 3) {
            cout << query1(1, 1, n, l, r) << "\n";
        } else {
            cout << query2(1, 1, n, l, r).mx << "\n";
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