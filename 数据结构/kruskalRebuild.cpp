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
const int M = 2e5 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m, q;

struct edg {
    int frm, to;
    int w;
    bool operator< (const edg &other) const {
        return w < other.w;
    }
}edge[N * 3];
int cnt;

void addEdge(int u, int v, int w) {
    edge[++cnt].frm = u;
    edge[cnt].to = v;
    edge[cnt].w = w;
}

int fa[N * 2];

int find(int x) {
    return fa[x] = fa[x] == x ? x : find(fa[x]);
}

struct kru {
    int to, nxt;
}edgek[N * 2];
int key[N * 2];
int headk[N * 2], cntk;
int tot;

int power;
int dep[N * 2], st[20][N * 2];

void addEdgek(int u, int v) {
    edgek[++cntk].to = v;
    edgek[cntk].nxt = headk[u];
    headk[u] = cntk;
}

void kruskalRebuild() {
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; ++i) {
        int fx = find(edge[i].frm);
        int fy = find(edge[i].to);
        if (fx == fy) continue;
        fa[fx] = fa[fy] = ++tot;
        key[tot] = edge[i].w;
        addEdgek(tot, fx);
        addEdgek(tot, fy);
    }
}

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    st[0][u] = fa;
    for (int p = 1; p <= power; ++p) {
        st[p][u] = st[p - 1][st[p - 1][u]];
    }
    for (int i = headk[u]; i; i = edgek[i].nxt) {
        int v = edgek[i].to;
        if (v == fa) continue;
        dfs1(v, u);
    }
}

int lca(int a, int b) {
    int dis = abs(dep[a] - dep[b]);
    if (dep[a] > dep[b]) {
        for (int p = power; p >= 0; --p) {
            if ((1 << p) > dis) continue;
            a = st[p][a];
            dis -= (1 << p);
        }
    }
    if (dep[a] < dep[b]) {
        for (int p = power; p >= 0; --p) {
            if ((1 << p) > dis) continue;
            b = st[p][b];
            dis -= (1 << p);
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = power; p >= 0; --p) {
        if (st[p][a] == st[p][b]) continue;
        a = st[p][a];
        b = st[p][b];
    }
    return st[0][a];
}


void init() {
    for (int i = 0; i <= n * 2; ++i) {
        fa[i] = i;
        headk[i] = 0;
    }
    cnt = 0;
    cntk = 0;
    tot = n;
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        addEdge(a, b, l);
    }
    kruskalRebuild();
    power = lg2(tot);
    for (int i = 1; i <= tot; ++i) {
        if (fa[i] == i) {
            dfs1(i, 0);
        }
    }
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        int fata = find(a);
        int fatb = find(b);
        if (fata != fatb) {
            cout << "impossible\n";
        } else {
            cout << key[lca(a, b)] << "\n";
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