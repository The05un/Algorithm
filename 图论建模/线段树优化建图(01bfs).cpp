#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 5e5 + 5;
const int MAXT = MAXN * 10;
const int MAXE = MAXN * 30;
const ll INF = 1LL << 60;
int n, q, s;

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cntg;

int ls[MAXT];
int rs[MAXT];
int rootOut, rootIn;
int cntt;

struct Node{
    int u;
    ll d;
    Node(int a, ll b) : u(a), d(b) {}
    bool operator< (const Node &other) const {
        return d > other.d;
    }
};
ll dist[MAXT];
bool vis[MAXT];
deque<int> dq;

void addEdge(int u, int v, int w) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg;
}

int buildOut(int l, int r) {
    int rt;
    if (l == r) {
        rt = l;
    } else {
        rt = ++cntt;
        int mid = (l + r) >> 1;
        ls[rt] = buildOut(l, mid);
        rs[rt] = buildOut(mid + 1, r);
        addEdge(ls[rt], rt, 0);
        addEdge(rs[rt], rt, 0);
    }
    return rt;
}
int buildIn(int l, int r) {
    int rt;
    if (l == r) {
        rt = l;
    } else {
        rt = ++cntt;
        int mid = (l + r) >> 1;
        ls[rt] = buildIn(l, mid);
        rs[rt] = buildIn(mid + 1, r);
        addEdge(rt, ls[rt], 0);
        addEdge(rt, rs[rt], 0);
    }
    return rt;
}

void xToRange(int jobx, int jobl, int jobr, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(jobx, i, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) xToRange(jobx, jobl, jobr, jobw, l, mid, ls[i]);
        if (jobr > mid) xToRange(jobx, jobl, jobr, jobw, mid + 1, r, rs[i]);
    }
}
void rangeToX(int jobl, int jobr, int jobx, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addEdge(i, jobx, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) rangeToX(jobl, jobr, jobx, jobw, l, mid, ls[i]);
        if (jobr > mid) rangeToX(jobl, jobr, jobx, jobw, mid + 1, r, rs[i]);
    }
}
void rangeToRange(int a, int b, int c, int d) {
    int x = ++cntt;
    int y = ++cntt;
    rangeToX(a, b, x, 0, 1, n, rootOut);
    xToRange(y, c, d, 0, 1, n, rootIn);
    addEdge(x, y, 1);
}

void bfs01() {
    for (int i = 1; i <= cntt; ++i) {
        dist[i] = INF;
    }
    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (int e = head[u]; e > 0; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
}

void solve() {
    cin >> n >> q >> s;
    cntt = n;
    rootOut = buildOut(1, n);
    rootIn = buildIn(1, n);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        rangeToRange(a, b, c, d);
        rangeToRange(c, d, a, b);
    }
    bfs01();
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << "\n";
        cout << dist[i];
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}