#include<bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define Rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
#define mem(x, v, n) memset(x, v, ((n) + 1) * sizeof((x)[0]))
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

const int N = 2e5 + 5;
const int M = 5000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m, s;
int arr[N];
int na[N];

struct sgt {
    int ls, rs;
    int siz;
}tr[N * 22];
int root[N], cnt;

int clone(int i) {
    tr[++cnt] = tr[i];
    return cnt;
}

int build(int pl, int pr) {
    int rt = ++cnt;
    if (pl == pr) {
        tr[rt].siz = 0;
    } else {
        int mid = (pl + pr) >> 1;
        tr[rt].ls = build(pl, mid);
        tr[rt].rs = build(mid + 1, pr);
    }
    return rt;
}

int insert(int rt, int pl, int pr, int x) {
    int r = clone(rt);
    tr[r].siz++;
    if (pl < pr) {
        int mid = (pl + pr) >> 1;
        if (x <= mid) tr[r].ls = insert(tr[r].ls, pl, mid, x);
        else tr[r].rs = insert(tr[r].rs, mid + 1, pr, x);
    }
    return r;
}

int query(int u, int v, int pl, int pr, int k) {
    if (pl == pr) {
        return pl;
    }
    int lsiz = tr[tr[v].ls].siz - tr[tr[u].ls].siz;
    int mid = (pl + pr) >> 1;
    if (lsiz >= k) {
        return query(tr[u].ls, tr[v].ls, pl, mid, k);
    } else {
        return query(tr[u].rs, tr[v].rs, mid + 1, pr, k - lsiz);
    }
}

void prepare() {
    sort(arr + 1, arr + n + 1);
    s = n;
    s = unique(arr + 1, arr + n + 1) - (arr + 1);
    rep(i, 1, n) na[i] = lower_bound(arr + 1, arr + s + 1, na[i]) - arr;
    root[0] = build(1, s);   
    rep(i, 1, n) {
        int x = na[i];
        root[i] = insert(root[i - 1], 1, s, x);
    }
}

void init() {
    cnt = 0;
}

void solve() {
    cin >> n >> m;
    rep(i, 1, n) {
        cin >> arr[i];
        na[i] = arr[i];
    }
    prepare();
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int pos = query(root[l - 1], root[r], 1, s, k);
        cout << arr[pos] << "\n";
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