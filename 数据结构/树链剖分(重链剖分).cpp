#include<bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define Rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
#define mem(x, v, sz) memset(x,v,(sz+1)*sizeof(int))
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
const int M = 2e5 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m, root, MOD;
int arr[N];

struct treeEdge {
    int to, nxt;
}edge[N << 1];
int head[N], cnt = 0;

struct tree {
    int fa;
    int dep, siz;
    int son;
    int top;
    int dfn;
}tr[N];
int seg[N], cntt = 0;

void init() {
    rep(i, 1, n) {
        head[i] = 0;
    }
    cnt = 0;
    cntt = 0;
}

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    tr[u].fa = fa;
    tr[u].dep = tr[fa].dep + 1;
    tr[u].siz = 1;
    tr[u].son = 0;
    int tmp = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        tr[u].siz += tr[v].siz;
        if (tr[v].siz > tmp) {
            tmp = tr[v].siz;
            tr[u].son = v;
        }
    }
}

void dfs2(int u, int t) {
    tr[u].top = t;
    tr[u].dfn = ++cntt;
    seg[cntt] = u;
    if (!tr[u].son) return;
    dfs2(tr[u].son, t);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == tr[u].fa || v == tr[u].son) continue;
        dfs2(v, v);
    }
}

struct sgt {
    int sum;
    int tag;
}ttr[N << 2];

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void push_up(int p) {
    ttr[p].sum = (ttr[ls(p)].sum + ttr[rs(p)].sum) % MOD;
}

void build(int p, int pl, int pr) {
    ttr[p].tag = 0;
    if (pl == pr) {
        ttr[p].sum = arr[seg[pl]] % MOD;
        return;
    }
    int mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addtag(int p, int pl, int pr, int v) {
    ttr[p].sum = (ttr[p].sum + (pr - pl + 1) % MOD * (v % MOD) % MOD) % MOD;
    ttr[p].tag = (v + ttr[p].tag) % MOD;
}

void push_down(int p, int pl, int pr) {
    if (ttr[p].tag == 0 || pl == pr) return;
    int mid = (pl + pr) >> 1;
    addtag(ls(p), pl, mid, ttr[p].tag);
    addtag(rs(p), mid + 1, pr, ttr[p].tag);
    ttr[p].tag = 0;
}

void update(int p, int pl, int pr, int L, int R, int x) {
    if (L <= pl && pr <= R) {
        addtag(p, pl, pr, x);
        return;
    }
    int mid = (pl + pr) >> 1;
    push_down(p, pl, pr);
    if (L <= mid) update(ls(p), pl, mid, L, R, x);
    if (R > mid) update(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

int query(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return ttr[p].sum;
    }
    int mid = (pl + pr) >> 1;
    push_down(p, pl, pr);
    int res = 0;
    if (L <= mid) res += query(ls(p), pl, mid, L, R);
    if (R > mid) res += query(rs(p), mid + 1, pr, L, R);
    res %= MOD;
    return res;
}

void pathAdd(int x, int y, int v) {
    while (tr[x].top != tr[y].top) {
        if (tr[tr[x].top].dep <= tr[tr[y].top].dep) {
            update(1, 1, n, tr[tr[y].top].dfn, tr[y].dfn, v);
            y = tr[tr[y].top].fa;
        } else {
            update(1, 1, n, tr[tr[x].top].dfn, tr[x].dfn, v);
            x = tr[tr[x].top].fa;
        }
    }
    update(1, 1, n, min(tr[x].dfn, tr[y].dfn), max(tr[x].dfn, tr[y].dfn), v);
}

void subAdd(int x, int v) {
    update(1, 1, n, tr[x].dfn, tr[x].dfn + tr[x].siz - 1, v);
}

int pathSum(int x, int y) {
    int res = 0;
    while (tr[x].top != tr[y].top) {
        if (tr[tr[x].top].dep <= tr[tr[y].top].dep) {
            res = (res + query(1, 1, n, tr[tr[y].top].dfn, tr[y].dfn)) % MOD;
            y = tr[tr[y].top].fa;
        } else {
            res = (res + query(1, 1, n, tr[tr[x].top].dfn, tr[x].dfn)) % MOD;
            x = tr[tr[x].top].fa;
        }
    }
    res = (res + query(1, 1, n, min(tr[x].dfn, tr[y].dfn), max(tr[x].dfn, tr[y].dfn))) % MOD;
    return res;
}

int subSum(int x) {
    return query(1, 1, n, tr[x].dfn, tr[x].dfn + tr[x].siz - 1) % MOD;
}

void solve() {
    cin >> n >> m >> root >> MOD;
    init();
    rep(i, 1, n) {
        cin >> arr[i];
    }
    Rep(i, 1, n) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            pathAdd(x, y, z);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << pathSum(x, y) << "\n";
        } else if (op == 3) {
            int x, z;
            cin >> x >> z;
            subAdd(x, z);
        } else {
            int x;
            cin >> x;
            cout << subSum(x) << "\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}