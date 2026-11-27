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

const int N = 1e4 + 5;
const int M = 1e5 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 eps = 1e-9;

int n, m;

struct gedge {
    int to, nxt;
}edge[M];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int dfn[N], cntu;
int low[N];
int belong[N];
stack<int> sta;
int cnts, idx;
int sccarr[N];
int sccl[N], sccr[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++cntu;
    sta.push(u);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else {
            if (!belong[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (low[u] == dfn[u]) {
        cnts++;
        sccl[cnts] = idx + 1;
        while (!sta.empty() && sta.top() != u) {
            int t = sta.top(); sta.pop();
            belong[t] = cnts;
            sccarr[++idx] = t;
        }
        sta.pop();
        belong[u] = cnts;
        sccarr[++idx] = u;
        sccr[cnts] = idx;
    }
}

int vis[N];

void init() {
    for (int i = 1; i <= n; ++i) {
        head[i] = 0;
        dfn[i] = belong[i] = 0;
        vis[i] = 0;
    }
    cnt = cntu = 0;
    cnts = idx = 0;
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    cout << cnts << "\n";

    for (int i = 1; i <= cnts; i++) {
        sort(sccarr + sccl[i], sccarr + sccr[i] + 1);
    }
    
    for (int i = 1; i <= n; ++i) {
        int b = belong[i];
        if (!vis[b]) {
            for (int j = sccl[b]; j <= sccr[b]; ++j) {
                cout << sccarr[j] << " ";
            }
            cout << "\n";
            vis[b] = 1;
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