#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 5;
const int MAXT = MAXN * 10;
const int MAXM = MAXN * 30;
const int INF = 1e9; 
int n, m, k;

struct edg {
    int from, to, nxt;
    int w;
}edge[MAXM];
int head[MAXT];
int cntg;

int ls[MAXT];
int rs[MAXT];
int rootOut, rootIn;
int cntt;

struct node {
    int cur;
    int spend;
    int cost;
    node(int a, int b, int c) : cur(a), spend(b), cost(c) {}
    bool operator< (const node &other) const {
        return cost > other.cost;
    }
};
int dist[MAXT][11], vis[MAXT][11];
priority_queue<node> heap;

void init() {
    cntg = 0;
    for (int i = 0; i < MAXT; ++i) head[i] = -1;
    for (int i = 0; i < MAXM; ++i) edge[i].nxt = -1;
}
void addedge(int u, int v, int w) {
    edge[cntg].from = u;
    edge[cntg].to = v;
    edge[cntg].w = w;
    edge[cntg].nxt = head[u];
    head[u] = cntg++;
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
        addedge(ls[rt], rt, 0);
        addedge(rs[rt], rt, 0);
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
        addedge(rt, ls[rt], 0);
        addedge(rt, rs[rt], 0);
    }
    return rt;
}

void xToRange(int jobx, int jobl, int jobr, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addedge(jobx, i, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) xToRange(jobx, jobl, jobr, jobw, l, mid, ls[i]);
        if (jobr > mid) xToRange(jobx, jobl, jobr, jobw, mid + 1, r, rs[i]);
    }
}
void rangeToX(int jobl, int jobr, int jobx, int jobw, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addedge(i, jobx, jobw);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) rangeToX(jobl, jobr, jobx, jobw, l, mid, ls[i]);
        if (jobr > mid) rangeToX(jobl, jobr, jobx, jobw, mid + 1, r, rs[i]);
    }
}
void rangeToRange(int a, int b, int c, int d, int w) {
    int x = ++cntt;
    int y = ++cntt;
    rangeToX(a, b, x, 0, 1, n, rootOut);
    xToRange(y, c, d, 0, 1, n, rootIn);
    addedge(x, y, w);
}

int dijkstra() {
    while (!heap.empty()) heap.pop();
    for (int i = 0; i < MAXT; ++i) {
        for (int j = 0; j < 11; ++j) {
            dist[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    heap.push(node(1, 0, 0));
    dist[1][0] = 0;
    while (!heap.empty()) {
        node t = heap.top(); heap.pop();
        int cur = t.cur;
        int spend = t.spend;
        int cost = t.cost;
        if (vis[cur][spend]) continue;
        if (cur == n) return cost;
        vis[cur][spend] = 1;
        for (int i = head[cur]; i != -1; i = edge[i].nxt) {
            int nextCity = edge[i].to;
            int nextSpend = spend + 1;
            int nextCost = cost + edge[i].w;
            if (spend < k) {
                if (!vis[nextCity][nextSpend] && dist[nextCity][nextSpend] > cost) {
                    dist[nextCity][nextSpend] = cost;
                    heap.push(node(nextCity, nextSpend, cost));
                }
            }
            if (!vis[nextCity][spend] && dist[nextCity][spend] > nextCost) {
                dist[nextCity][spend] = nextCost;
                heap.push(node(nextCity, spend, nextCost));
            }
        }
    }
    return -1;
}

void solve() {
    cin >> n >> m >> k;
    init();
    cntt = n;
    rootOut = buildOut(1, n);
    rootIn = buildIn(1, n);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d, w;
        cin >> a >> b >> c >> d >> w;
        rangeToRange(a, b, c, d, w);
        rangeToRange(c, d, a, b, w);
    }
    int res = dijkstra();
    if (res != -1) {
        cout << res << "\n";
    } else {
        cout << "CreationAugust is a sb!\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}