#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 5e5 + 5;
const int M = 1000 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const double gama = 1e-9;

int n, m, s;
struct edg {
    int from, to, nxt;
}edge[N * 2];
int head[N], cnt = 0;
int power;
int stjump[20][N];
int deep[N];

void init() {
    for (int i = 0; i <= cnt; ++i) {
        edge[i].nxt = 0;
    }
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
    }
    cnt = 0;
}

void addEdge(int u, int v) {
    edge[++cnt].from = u;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int lg2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void dfs(int u, int fa) {
    if (u == s) {
        deep[u] = 1;
    } else {
        deep[u] = deep[fa] + 1;
    }
    stjump[0][u] = fa;
    for (int p = 1; p <= power; ++p) {
        stjump[p][u] = stjump[p - 1][stjump[p - 1][u]];
    }
    for (int i = head[u]; i; i = edge[i].nxt) {
        if (edge[i].to != fa) dfs(edge[i].to ,u);
    }
}

int query(int a, int b) {
    int dis = abs(deep[a] - deep[b]);
    if (deep[a] > deep[b]) {
        for (int p = power; p >= 0; --p) {
            if ((1 << p) > dis) continue;
            a = stjump[p][a];
            dis -= (1 << p);
            if (!dis) break;
        }
    }
    if (deep[b] > deep[a]) {
        for (int p = power; p >= 0; --p) {
            if ((1 << p) > dis) continue;
            b = stjump[p][b];
            dis -= (1 << p);
            if (!dis) break;
        }
    }
    if (a == b) {
        return a;
    }
    int d = deep[a] - 1;
    for (int p = power; p >= 0; --p) {
        if ((1 << p) > d) continue;
        if (stjump[p][a] == stjump[p][b]) continue;
        a = stjump[p][a];
        b = stjump[p][b];
        d -= (1 << p);
    }
    int fa = stjump[0][a];
    return fa;
}

void solve() {
    cin >> n >> m >> s;
    init();
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    power = lg2(n);
    dfs(s, 0);
    while (m--) {
        int a, b;
        cin >> a >> b;
        int ans = query(a, b);
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}