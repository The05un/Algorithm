#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N  = 3e5 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

int n, s;

struct edg {
    int from, to, nxt;
    int w;
}edge[N * 2];
int head[N], cnt = 0;

int last[N];
int dist[N];
int best, po;
int d;
int vis[N], dp[N];
int pred[N];

void init() {
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
        vis[i] = 0;
    }
    cnt = 0;
}

void addEdge(int u, int v, int w) {
    edge[++cnt].from = u;
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
} 

void dfs(int u, int fa, int we) {
    last[u] = fa;
    pred[u] = we;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        int w = edge[i].w;
        if (v == fa) continue;
        dist[v] = dist[u] + w;
        if (dist[v] > best) {
            best = dist[v];
            po = v;
        }
        dfs(v, u, w);
    }
}

void find_d(int st) {
    po = st;
    best = 0;
    dist[st] = 0;
    dfs(st, 0, 0);

    st = po;
    best = 0;
    dist[st] = 0;
    dfs(st, 0, 0);

    d = best;
}

void tree_dp(int u, int fa) {
    dp[u] = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        int w = edge[i].w;
        if (v == fa) continue;
        if (vis[v]) continue;
        tree_dp(v, u);
        dp[u] = max(dp[u], dp[v] + w);
    }
}

int compute() {
    deque<int> dq;
    int ans = INT_MAX;
    int suml = 0, sumr = 0;
    for (int l = po, r = po; l; l = last[l]) {
        while (r && sumr - suml + pred[r] <= s) {
            while (!dq.empty() && dp[dq.back()] <= dp[r]) {
                dq.pop_back();
            }
            sumr += pred[r];
            dq.push_back(r);
            r = last[r];
        }
        ans = min(ans, max({suml, d - sumr, dq.empty() ? 0 : dp[dq.front()]}));
        suml += pred[l];
    }
    return ans;
}

void solve() {
    cin >> n >> s;
    init();
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    find_d(1);
    for (int i = po; i; i = last[i]) {
        vis[i] = 1;
    }
    for (int i = po; i; i = last[i]) {
        tree_dp(i, 0);
    }

    int res = compute();
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}