#include<bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x" = " << (x) << "\n"
#define pp(x, y) cout << "pp: " << (x) << " " << (y) << "\n"

#define int long long

#define fi first
#define se second
#define pir pair<int, int>
#define i64 long long
#define u64 unsigned long long
#define u32 unsigned
#define i128 __int128
#define u128 unsigned __int128
#define f64 double
#define ld long double

const int N = 1e5 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;
int arr[N];
int root[N], t;

struct psgt {
    int ls, rs;
    int sum, tag;
}tr[N << 8];
int cnt;

int clone(int p) {
    tr[++cnt] = tr[p];
    return cnt;
}

void up(int p) {
    tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum;
}

void lazy(int p, int v, int n) {
    tr[p].sum += v * n;
    tr[p].tag += v;
}

void down(int p, int ln, int rn) {
    if (tr[p].tag) {
        tr[p].ls = clone(tr[p].ls);
        tr[p].rs = clone(tr[p].rs);
        lazy(tr[p].ls, tr[p].tag, ln);
        lazy(tr[p].rs, tr[p].tag, rn);
        tr[p].tag = 0;
    }
}

int build(int pl, int pr) {
    int rt = ++cnt;
    tr[rt].tag = 0;
    if (pl == pr) {
        tr[rt].sum = arr[pl];
    } else {
        int mid = (pl + pr) >> 1;
        tr[rt].ls = build(pl, mid);
        tr[rt].rs = build(mid + 1, pr);
        up(rt);
    }
    return rt;
}

int add(int p, int pl, int pr, int L, int R, int v) {
    int rt = clone(p);
    if (L <= pl && pr <= R) {
        lazy(rt, v, pr - pl + 1);
    } else {
        int mid = (pl + pr) >> 1;
        down(rt, mid - pl + 1, pr - mid);
        if (L <= mid) tr[rt].ls = add(tr[rt].ls, pl, mid, L, R, v);
        if (R > mid) tr[rt].rs = add(tr[rt].rs, mid + 1, pr, L, R, v);
        up(rt);
    }
    return rt;
}

int query(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return tr[p].sum;
    } else {
        int mid = (pl + pr) >> 1;
        down(p, mid - pl + 1, pr - mid);
        int ans = 0;
        if (L <= mid) ans += query(tr[p].ls, pl, mid, L, R);
        if (R > mid) ans += query(tr[p].rs, mid + 1, pr, L, R);
        return ans;
    }
}

void init() {
    t = 0;
    cnt = 0;
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    root[0] = build(1, n);
    for (int i = 1; i <= m; ++i) {
        char op; cin >> op;
        if (op == 'C') {
            int l, r, d;
            cin >> l >> r >> d;
            root[t + 1] = add(root[t], 1, n, l, r, d);
            t++;
        } else if (op == 'Q') {
            int l, r;
            cin >> l >> r;
            int tmp = query(root[t], 1, n, l, r);
            cout << tmp << "\n";
        } else if (op == 'H') {
            int l, r, z;
            cin >> l >> r >> z;
            int tmp = query(root[z], 1, n, l, r);
            cout << tmp << "\n";
        } else {
            int x; cin >> x;
            t = x;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; 
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}