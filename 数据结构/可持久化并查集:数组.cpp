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

const int N = 3e5 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;

int rtfa[N];
int rtsiz[N];

struct parr {
    int ls, rs;
    int val;
}tr[N << 5];
int cnt;

int clone(int p) {
    tr[++cnt] = tr[p];
    return cnt;
}

int buildfa(int pl, int pr) {
    int rt = ++cnt;
    if (pl == pr) {
        tr[rt].val = pl;
    } else {
        int mid = (pl + pr) >> 1;
        tr[rt].ls = buildfa(pl, mid);
        tr[rt].rs = buildfa(mid + 1, pr);
    }
    return rt;
}

int buildsiz(int pl, int pr) {
    int rt = ++cnt;
    if (pl == pr) {
        tr[rt].val = 1;
    } else {
        int mid = (pl + pr) >> 1;
        tr[rt].ls = buildsiz(pl, mid);
        tr[rt].rs = buildsiz(mid + 1, pr);
    }
    return rt;
}

int update(int p, int pl, int pr, int x, int v) {
    int rt = clone(p);
    if (pl == pr) {
        tr[rt].val = v;
    } else {
        int mid = (pl + pr) >> 1;
        if (x <= mid) tr[rt].ls = update(tr[rt].ls, pl, mid, x, v);
        else tr[rt].rs = update(tr[rt].rs, mid + 1, pr, x, v);
    }
    return rt;
}

int query(int p, int pl, int pr, int x) {
    if (pl == pr) {
        return tr[p].val;
    } else {
        int mid = (pl + pr) >> 1;
        if (x <= mid) return query(tr[p].ls, pl, mid, x);
        else return query(tr[p].rs, mid + 1, pr, x);
    }
}

// 基于v版本，查询x的集合头节点
int find(int x, int v) {
    int fa = query(rtfa[v], 1, n, x);
    while (x != fa) {
        x = fa;
        fa = query(rtfa[v], 1, n, x);
    }
    return x;
}

void merge(int x, int y, int v) {
    int fx = find(x, v);
    int fy = find(y, v);
    if (fx != fy) {
        int xsiz = query(rtsiz[v], 1, n, fx);
        int ysiz = query(rtsiz[v], 1, n, fy);
        if (xsiz >= ysiz) {
            rtfa[v] = update(rtfa[v], 1, n, fy, fx);
            rtsiz[v] = update(rtsiz[v], 1, n, fx, xsiz + ysiz);
        } else {
            rtfa[v] = update(rtfa[v], 1, n, fx, fy);
            rtsiz[v] = update(rtsiz[v], 1, n, fy, xsiz + ysiz);
        }
    }
}

void init() {
    cnt = 0;
}

void solve() {
    cin >> n >> m;
    init();
    rtfa[0] = buildfa(1, n);
    rtsiz[0] = buildsiz(1, n);
    for (int i = 1; i <= m; ++i) {
        int op; cin >> op;
        rtfa[i] = rtfa[i - 1];
        rtsiz[i] = rtsiz[i - 1];
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            merge(a, b, i);
        } else if (op == 2) {
            int v; cin >> v;
            rtfa[i] = rtfa[v];
            rtsiz[i] = rtsiz[v];
        } else {
            int x, y;
            cin >> x >> y;
            cout << (find(x, i) == find(y, i)) << "\n";
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