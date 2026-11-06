#include<bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define Rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
#define mem(x, v, sz) memset(x,v,(sz+1)*sizeof(int))
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

const int N = 5e3 + 5;
const int M = 2e5 + 5;
const int mod = 998244353;
const int INF = 1e18;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;
f64 money;

struct edgg {
    int to, nxt;
    f64 w;
}edgeg[M];
int headg[N], cntg = 0;

struct edgr {
    int to, nxt;
    f64 w;
}edger[M];
int headr[N], cntr = 0;

struct lft {
    f64 cost;
    int ls, rs;
    int dist;
    int to;
}tr[M * 5];
int root[N], cntt = 0;

int vis[N];
int path[N];
f64 dis[N];

priority_queue<pair<f64, int>, vector<pair<f64, int>>, greater<pair<f64, int>>> heap1;

priority_queue<pair<f64, int>, vector<pair<f64, int>>, greater<pair<f64, int>>> heap2;

void clean() {
    mem(headg, 0, n);
    mem(headr, 0, n);
    cntg = 0;
    cntr = 0;
    mem(vis, 0, n);
    tr[0].dist = -1;
}

void addEdgeG(int u, int v, f64 w) {
    edgeg[++cntg].to = v;
    edgeg[cntg].w = w;
    edgeg[cntg].nxt = headg[u];
    headg[u] = cntg;
}

void addEdgeR(int u, int v, f64 w) {
    edger[++cntr].to = v;
    edger[cntr].w = w;
    edger[cntr].nxt = headr[u];
    headr[u] = cntr;
}

int init(int t, f64 c) {
    tr[++cntt].to = t;
    tr[cntt].cost = c;
    tr[cntt].ls = tr[cntt].rs = tr[cntt].dist = 0;
    return cntt;
}

int clone(int i) {
    tr[++cntt] = tr[i];
    return cntt;
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (tr[i].cost > tr[j].cost) {
        swap(i, j);
    }
    int h = clone(i);
    tr[h].rs = merge(tr[h].rs, j);
    if (tr[tr[h].ls].dist < tr[tr[h].rs].dist) {
        swap(tr[h].ls, tr[h].rs);
    }
    tr[h].dist = tr[tr[h].rs].dist + 1;
    return h;
}

void dijkstra() {
    dis[n] = 0;
    path[n] = 0;
    fill(dis + 1, dis + n, INF);
    heap1.push({0, n});
    while (!heap1.empty()) {
        auto top = heap1.top(); heap1.pop();
        int u = top.se;
        f64 w = top.fi;
        if (!vis[u]) {
            vis[u] = 1;
            for (int i = headr[u]; i; i = edger[i].nxt) {
                int v = edger[i].to;
                f64 nw = w + edger[i].w;
                if (dis[v] > nw) {
                    dis[v] = nw;
                    path[v] = i;
                    heap1.push({dis[v], v});
                }
            }
        }
    }
}

void mergeRoad() {
    rep(i, 1, n) {
        heap1.push({dis[i], i});
    }
    while (!heap1.empty()) {
       auto top = heap1.top(); heap1.pop();
        int u = top.se;
        for (int i = headg[u]; i; i = edgeg[i].nxt) {
            if (i == path[u]) continue;
            int v = edgeg[i].to;
            root[u] = merge(root[u], init(v, edgeg[i].w + dis[v] - dis[u]));
        }
        if (path[u] != 0) {
            root[u] = merge(root[u], root[edgeg[path[u]].to]);
        }
    }
}

int expand() {
    int res = 0;
    money -= dis[1];
    if (money >= 0) {
        res++;
        if (root[1]) {
            heap2.push({dis[1] + tr[root[1]].cost, root[1]});
        }
        while (!heap2.empty()) {
            auto top = heap2.top(); heap2.pop();
            int h = top.se;
            f64 w = top.fi;
            money -= w;
            if (money < 0) {
                break;
            }
            res++;
            if (tr[h].ls) {
                heap2.push({w - tr[h].cost + tr[tr[h].ls].cost, tr[h].ls});
            }
            if (tr[h].rs) {
                heap2.push({w - tr[h].cost + tr[tr[h].rs].cost, tr[h].rs});
            }
            if (tr[h].to && root[tr[h].to]) {
                heap2.push({w + tr[root[tr[h].to]].cost, root[tr[h].to]});
            }
        }
    }
    return res;
}

void solve() {
    cin >> n >> m;
    cin >> money;
    clean();
    rep(i, 1, m) {
        int u, v;
        f64 w;
        cin >> u >> v >> w;
        if (u == n) continue;
        addEdgeG(u, v, w);
        addEdgeR(v, u, w);
    }
    dijkstra();
    mergeRoad();
    int ans = expand();
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}