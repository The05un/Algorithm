#include<bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define Rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
#define mem(x, v, n) memset(x, v, ((n) + 1) * sizeof((x)[0]))
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

const int N = 5e5 + 5;
const int M = 5000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, q;
int root;

u32 s;
u32 get(u32 x) {
    x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}

struct trEdge {
    int to, nxt;
}edge[N * 2];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

struct tree {
    int fa, son;
    int dep, len;
    int dfn, top;
}tr[N];
int cntt;

int st[20][N], power;

int high[N];
int up[N], down[N];

void setup(int u, int i, int v) {
    up[tr[u].dfn + i] = v;
}

int getup(int u, int i) {
    return up[tr[u].dfn + i];
}

void setdown(int u, int i, int v) {
    down[tr[u].dfn + i] = v;
}

int getdown(int u, int i) {
    return down[tr[u].dfn + i];
}

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs1(int u, int fa) {
    st[0][u] = fa;
    rep(p, 1, power) {
        st[p][u] = st[p - 1][st[p - 1][u]];
    }
    tr[u].dep = tr[fa].dep + 1;
    tr[u].fa = fa;
    tr[u].len = 1;
    tr[u].son = 0;
    int tmp = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        if (tr[v].len > tmp) {
            tmp = tr[v].len;
            tr[u].son = v;
        }
        tr[u].len = tmp + 1;
    }
}

void dfs2(int u, int t) {
    tr[u].top = t;
    tr[u].dfn = ++cntt;
    if (!tr[u].son) return;
    dfs2(tr[u].son, t);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == tr[u].fa || v == tr[u].son) continue;
        dfs2(v, v);
    }
}

void prepare() {
    high[0] = -1;
    rep(i, 1, n) {
        high[i] = high[i / 2] + 1;
    }
    rep(u, 1, n) {
        if (tr[u].top == u) {
            int a = u;
            int b = u;
            for (int i = 0; i < tr[u].len; ++i) {
                setup(u, i, a);
                setdown(u, i, b);
                a = tr[a].fa;
                b = tr[b].son;
            }
        }
    }
}

int query(int x, int k) {
    if (k == 0) {
        return x;
    }
    if (k == (1 << high[k])) {
        return st[high[k]][x];
    }
    x = st[high[k]][x];
    k -= (1 << high[k]);
    k -= tr[x].dep - tr[tr[x].top].dep;
    x = tr[x].top;
    return (k > 0) ? getup(x, k) : getdown(x, -k);
}
    
void init() {
    rep(i, 1, n) {
        head[i] = 0;
    }
    cnt = 0;
    cntt = 0;
}

void solve() {
    cin >> n >> q >> s;
    init();
    rep(i, 1, n) {
        int f; cin >> f;
        if (f == 0) {
            root = i;
            continue;
        }
        addEdge(i, f);
        addEdge(f, i);
    }
    power = lg2(n);
    dfs1(root, 0);
    dfs2(root, root);
    prepare();
    int ans = 0;
    int lstans = 0;
    int cnt = 0;
    while (q--) {
        int x, k;
        x = (get(s) ^ lstans) % n + 1;
        k = (get(s) ^ lstans) % tr[x].dep;
        lstans = query(x, k);
        ans ^= (++cnt) * lstans;
    }
    cout << ans << "\n";
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