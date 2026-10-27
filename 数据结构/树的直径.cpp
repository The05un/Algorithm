#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 2e5 + 5;

int n;
struct edg {
    int from, to, nxt;
    int w;
}edge[N * 2];
int cnt;
int head[N];
int dist[N];

void init() {
    cnt = 0;
    for (int i = 0; i < N * 2; ++i) edge[i].nxt = -1;
    for (int i = 0; i < N; ++i) head[i] = -1;
}
void addEdge(int u, int v, int w) {
    edge[cnt].from = u;
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt++;
}

void dfs(int u, int father, int d) {
    dist[u] = d;
    for (int i = head[u]; i != -1; i = edge[i].nxt) {
        if (edge[i].to != father) {
            dfs(edge[i].to, u, d + edge[i].w);
        }
    }
}

void solve() {
    init();
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v, 1);
        addEdge(v, u, 1);
    }
    dfs(1, -1, 0);
    int s = 1;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > dist[s]) s = i;
    }
    dfs(s, -1, 0);
    int t = 1;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > dist[t]) t = i;
    }
    cout << dist[t] << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}