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
const int M = 2e6 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 eps = 1e-9;

int n, m;

struct gedge {
    int to, nxt;
}edge[M << 1];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int dfn[N], cntu;
int low[N];
int cut[M];

void tarjan(int u, int pre) {
    dfn[u] = low[u] = ++cntu;
    for (int i = head[u]; i; i = edge[i].nxt) {
        if ((i ^ 1) == pre) continue;
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                cut[i >> 1] = 1;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void init() {
    for (int i = 1; i <= n; ++i) {
        head[i] = 0;
        dfn[i] = low[i] = 0;
        cut[i] = 0;
    }
    cnt = 1;
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
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i, 0);
    }
    int ccnt = 0;
    for (int i = 1; i <= m; ++i) {
        if (cut[i]) ccnt++;
    }
    cout << ccnt << "\n";
    for (int i = 1; i <= m; ++i) {
        if (cut[i]) cout << i << " ";
    }
    cout << "\n";
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