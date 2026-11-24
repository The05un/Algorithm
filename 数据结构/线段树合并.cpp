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

const int N = 1e5 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n;
int arr[N];
int sor[N], cnt;
int ans[N];

struct tedge {
    int to, nxt;
}edge[N << 1];
int head[N], cnte;

void addEdge(int u, int v) {
    edge[++cnte].to = v;
    edge[cnte].nxt = head[u];
    head[u] = cnte;
}

void prepare() {
    sort(sor + 1, sor + n + 1);
    cnt = unique(sor + 1, sor + n + 1) - (sor + 1);
    for (int i = 1; i <= n; ++i) {
        arr[i] = lower_bound(sor + 1, sor + cnt + 1, arr[i]) - sor;
    }
}

struct sgt {
    int ls, rs;
    int siz;
}tr[N * 20];
int root[N], cnts;

void push_up(int p) {
    tr[p].siz = tr[tr[p].ls].siz + tr[tr[p].rs].siz;
}

int add(int p, int pl, int pr, int x) {
    int rt = p;
    if (!rt) {
        rt = ++cnts;
    }
    if (pl == pr) {
        tr[rt].siz++;
    } else {
        int mid = (pl + pr) >> 1;
        if (x <= mid) tr[rt].ls = add(tr[rt].ls, pl, mid, x);
        else tr[rt].rs = add(tr[rt].rs, mid + 1, pr, x);
        push_up(rt);
    }
    return rt;
}

int merge(int t1, int t2, int pl, int pr) {
    if (!t1 || !t2) {
        return t1 + t2;
    }
    if (pl == pr) {
        tr[t1].siz += tr[t2].siz;
    } else {
        int mid = (pl + pr) >> 1;
        tr[t1].ls = merge(tr[t1].ls, tr[t2].ls, pl, mid);
        tr[t1].rs = merge(tr[t1].rs, tr[t2].rs, mid + 1, pr);
        push_up(t1);
    }
    return t1;
}

int query(int p, int pl, int pr, int L, int R) {
    if (pl > pr || !p) {
        return 0;
    }
    if (L <= pl && pr <= R) {
        return tr[p].siz;
    }
    int mid = (pl + pr) >> 1;
    int res = 0;
    if (L <= mid) res += query(tr[p].ls, pl, mid, L, R);
    if (R > mid) res += query(tr[p].rs, mid + 1, pr, L, R);
    return res;
}

void dfs(int u, int fa) {
    root[u] = add(root[u], 1, cnt, arr[u]);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], 1, cnt);
    }
    ans[u] = query(root[u], 1, cnt, arr[u] + 1, cnt);
}

void init() {
    for (int i = 0; i <= n; ++i) {
        head[i] = 0;
        ans[i] = 0;
    }
    cnt = cnte = cnts = 0;
}

void solve() {
    cin >> n;
    init();
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        sor[i] = arr[i];
    }
    prepare();
    for (int i = 2; i <= n; ++i) {
        int f; cin >> f;
        addEdge(i, f);
        addEdge(f, i);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << "\n";
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