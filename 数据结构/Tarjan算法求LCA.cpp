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
    int to, nxt;
}edge[N * 2];
int ehead[N], ecnt;

struct query {
    int to, nxt;
    int index;
}qu[N * 2];
int qhead[N], qcnt;

int vis[N];
int ans[N];

int father[N];
stack<int> st;


void init() {
    for (int i = 0; i <= n; ++i) {
        ehead[i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        qhead[i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        vis[i] = 0;
    }
    ecnt = 0;
    qcnt = 0;
    for (int i = 0; i <= n; ++i) {
        father[i] = i;
    }
}

void addEdge(int u, int v) {
    edge[++ecnt].to = v;
    edge[ecnt].nxt = ehead[u];
    ehead[u] = ecnt;
}

void addQuery(int u, int v, int i) {
    qu[++qcnt].to = v;
    qu[qcnt].index = i;
    qu[qcnt].nxt = qhead[u];
    qhead[u] = qcnt;
}

int find(int x) {
    while (x != father[x]) {
        st.push(x);
        x = father[x];
    }
    while (!st.empty()) {
        int t = st.top(); st.pop();
        father[t] = x;
    }
    return x;
}

void tarjan(int u, int fa) {
    vis[u] = 1;
    for (int i = ehead[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v != fa) {
            tarjan(v, u);
            father[v] = u;
        }
    }
    for (int i = qhead[u]; i; i = qu[i].nxt) {
        int v = qu[i].to;
        if (vis[v]) {
            ans[qu[i].index] = find(v);
        }
    }
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
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        addQuery(a, b, i);
        addQuery(b, a, i);
    }
    tarjan(s, 0);
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}