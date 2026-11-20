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

const int N = 3e5 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n;
int arr[N][2];

struct tegde {
    int to, nxt;
}edge[N << 1];
int head[N], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int fa[N];
int siz[N];
int ec[N];

int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}

void merge(int x, int y) {
    fa[y] = x;
    siz[x] += siz[y];
    ec[x] += ec[y] + 1;
}

int ball;
int ans[N];
struct inf {
    int bg, sm;
    inf(int a, int b) : bg(a), sm(b) {}
};
stack<inf> st;

void dfs(int u, int f) {
    int fx = find(arr[u][0]);
    int fy = find(arr[u][1]);
    if (siz[fx] < siz[fy]) swap(fx, fy);
    bool added = 0;
    bool merged = 0;
    if (fx == fy) {
        if (ec[fx] < siz[fx]) {
            added = 1;
            ball++;
        }
        ec[fx]++;
    } else {
        if (ec[fx] < siz[fx] || ec[fy] < siz[fy]) {
            added = 1;
            ball++;
        }
        merged = 1;
        merge(fx, fy);
        st.push(inf(fx, fy));
    }
    ans[u] = ball;

    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == f) continue;
        dfs(v, u);
    }

    if (added) ball--;
    if (merged) {
        inf t = st.top(); st.pop();
        int p = t.bg;
        int q = t.sm;
        fa[q] = q;
        siz[p] -= siz[q];
        ec[p] -= ec[q] + 1;
    } else {
        ec[fx]--;
    }
}

void init() {
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
        fa[i] = i;
        siz[i] = 1;
        ec[i] = 0;
        ans[i] = 0;
    }
    cnt = ball = 0;
}

void solve() {
    cin >> n;
    init();
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i][0] >> arr[i][1];
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs(1, 0);
    for (int i = 2; i <= n; ++i) {
        cout << ans[i] << " ";
    } cout << "\n";
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