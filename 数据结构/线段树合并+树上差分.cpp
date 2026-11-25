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
const int s = 1e5 + 1;

struct tedge {
    int to, nxt;
}edge[N << 1];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int dep[N], power;
int st[20][N];

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs1(int u, int fa) {
    if (u == 1) {
        dep[u] = 1;
    } else {
        dep[u] = dep[fa] + 1;
    }
    st[0][u] = fa;
    for (int i = 1; i <= power; ++i) {
        st[i][u] = st[i - 1][st[i - 1][u]];
    }
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
    }
}

int lca(int a, int b) {
    int dis = abs(dep[a] - dep[b]);
    if (dep[a] < dep[b]) {
        for (int i = power; i >= 0; --i) {
            if ((1 << i) > dis) continue;
            dis -= (1 << i);
            b = st[i][b];
        }
    } else if (dep[a] > dep[b]) {
        for (int i = power; i >= 0; --i) {
            if ((1 << i) > dis) continue;
            dis -= (1 << i);
            a = st[i][a];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = power; i >= 0; --i) {
        if (st[i][a] == st[i][b]) continue;
        a = st[i][a];
        b = st[i][b];
    }
    return st[0][a];
}

struct sgt {
    int ls, rs;
    int mx;
}tr[N << 6];
int root[N], cnts;

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void up(int p) {
    tr[p].mx = max(tr[tr[p].ls].mx, tr[tr[p].rs].mx);
}

int add(int p, int pl, int pr, int x, int v) {
    int rt = p;
    if (!rt) {
        rt = ++cnts;
    }
    if (pl == pr) {
        if (v == 1) tr[rt].mx++;
        else tr[rt].mx--;
    } else {
        int mid = (pl + pr) >> 1;
        if (x <= mid) tr[rt].ls = add(tr[rt].ls, pl, mid, x, v);
        else tr[rt].rs = add(tr[rt].rs, mid + 1, pr, x, v);
        up(rt);
    }
    return rt;
}

int merge(int p1, int p2, int pl, int pr) {
    if (!p1 || !p2) {
        return p1 + p2;
    }
    if (pl == pr) {
        tr[p1].mx += tr[p2].mx;
    } else {
        int mid = (pl + pr) >> 1;
        tr[p1].ls = merge(tr[p1].ls, tr[p2].ls, pl, mid);
        tr[p1].rs = merge(tr[p1].rs, tr[p2].rs, mid + 1, pr);
        up(p1);
    }
    return p1;
}

int query(int p, int pl, int pr) {
    if (pl == pr) {
        return pl;
    } else {
        int mid = (pl + pr) >> 1;
        if (tr[tr[p].ls].mx >= tr[tr[p].rs].mx) {
            return query(tr[p].ls, pl, mid);
        } else {
            return query(tr[p].rs, mid + 1, pr);
        }
    }
}

int ans[N];

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs2(v, u);
        root[u] = merge(root[u], root[v], 1, s);
    }
    ans[u] = tr[root[u]].mx ? query(root[u], 1, s) : 0;
}

void init() {
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
    }
    cnt = cnts = 0;
    power = lg2(n);
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(1, 0);
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        int f = lca(x, y);
        int g = st[0][f];
        root[x] = add(root[x], 1, s, z, 1);
        root[y] = add(root[y], 1, s, z, 1);
        root[f] = add(root[f], 1, s, z, -1);
        if (g) root[g] = add(root[g], 1, s, z, -1);
    }
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << "\n";
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