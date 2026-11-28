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

const int N = 5e5 + 5;
const int M = 1e6 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 eps = 1e-9;

int n, m, q;

struct gedge {
    int to, nxt;
}edge[M << 1];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int cntn;
int dfn[N], cntu;
int low[N];
stack<int> sta;

struct tedge {
    int to, nxt;
}edge1[M << 2];
int head1[N << 1], cnt1;

void addEdge1(int u, int v) {
    edge1[++cnt1].to = v;
    edge1[cnt1].nxt = head1[u];
    head1[u] = cnt1;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cntu;
    sta.push(u);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cntn++;
                addEdge1(cntn, u);
                addEdge1(u, cntn);
                while (!sta.empty() && sta.top() != v) {
                    int t = sta.top(); sta.pop();
                    addEdge1(cntn, t);
                    addEdge1(t, cntn);
                }
                sta.pop();
                addEdge1(cntn, v);
                addEdge1(v, cntn);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int dep[N << 1], power;
int st[20][N << 1];

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    st[0][u] = fa;
    for (int i = 1; i <= power; ++i) {
        st[i][u] = st[i - 1][st[i - 1][u]];
    }
    for (int i = head1[u]; i; i = edge1[i].nxt) {
        int v = edge1[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    int d = abs(dep[a] - dep[b]);
    if (dep[a] < dep[b]) {
        for (int i = power; i >= 0; --i) {
            if ((1 << i) > d) continue;
            d -= (1 << i);
            b = st[i][b];
        }
    } else if (dep[b] < dep[a]) {
        for (int i = power; i >= 0; --i) {
            if ((1 << i) > d) continue;
            d -= (1 << i);
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

int getd(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

void init() {
    for (int i = 1; i <= n; ++i) {
        head[i] = 0;
        dfn[i] = low[i] = 0;
        dep[i] = 0;
    }
    cnt = cnt1 = 0;
    cntn = n;
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    tarjan(1);
    power = lg2(cntn);
    dfs(1, 0);
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        cout << getd(a, b) / 2 + 1 << "\n";
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