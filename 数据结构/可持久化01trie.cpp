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

int n, q;

struct tedge {
    int to, nxt;
    string s;
}edge[N << 1];
int head[N], cnt;

void addEdge(int u, int v, string c) {
    edge[++cnt].to = v;
    edge[cnt].s = c;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

struct trie01 {
    int s[26];
    int ps;
}tr[N * 30];   //按量开，这里开炸了
int cntt;
int root[N];

int clone(int p) {
    tr[++cntt] = tr[p];
    tr[cntt].ps++;
    return cntt;
}

int insert(int r, const string &s) {
    int rt = clone(r);
    int pre = rt, cur;
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int ch = s[i] - 'a';
        r = tr[r].s[ch];
        cur = clone(r);
        tr[pre].s[ch] = cur;
        pre = cur;
    }
    return rt;
}

int query(int r, const string &s) {
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int ch = s[i] - 'a';
        r = tr[r].s[ch];
        if (!r) return 0;
    }
    return tr[r].ps;
}

int st[20][N];
int dep[N], power;

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs(int u, int fa, string t) {
    root[u] = insert(root[fa], t);
    if (u == 1) dep[u] = 1;
    else dep[u] = dep[fa] + 1;
    st[0][u] = fa;
    for (int i = 1; i <= power; ++i) {
        st[i][u] = st[i - 1][st[i - 1][u]];
    }
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        string tt = edge[i].s;
        if (v == fa) continue;
        dfs(v, u, tt);
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
    }
    if (dep[a] > dep[b]) {
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

int compute(int u, int v, string te) {
    return query(root[u], te) + query(root[v], te) - 2 * query(root[lca(u, v)], te);
}

void init() {
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
    }
    cnt = cntt = 0;
    power = lg2(n);
}

void solve() {
    cin >> n;
    init();
    for (int i = 1; i < n; ++i) {
        int a, b;
        string c;
        cin >> a >> b >> c;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    root[0] = insert(0, "");
    dfs(1, 0, "");

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int a, b;
        string v;
        cin >> a >> b >> v;
        cout << compute(a, b, v) << "\n";
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