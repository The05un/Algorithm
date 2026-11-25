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
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, q;
string s, t;
int l, r;

struct SAM {
    struct node {
        int son[26];
        int fa, len;
        int pos;
    }tr[N << 1];
    int tot, np;

    void init() {
        tot = np = 1;
        tr[1] = node{};
    }

    void insert(int c, int pos) {
        int p = np;
        np = ++tot;
        tr[np] = node{};
        tr[np].len = tr[p].len + 1;
        tr[np].pos = pos;

        while (p && !tr[p].son[c]) {
            tr[p].son[c] = np;
            p = tr[p].fa;
        }

        if (!p) {
            tr[np].fa = 1;
        } else {
            int q = tr[p].son[c];
            if (tr[p].len + 1 == tr[q].len) {
                tr[np].fa = q;
            } else {
                int nq = ++tot;
                tr[nq] = tr[q];
                tr[nq].len = tr[p].len + 1;
                tr[q].fa = tr[np].fa = nq;
                while (p && tr[p].son[c] == q) {
                    tr[p].son[c] = nq;
                    p = tr[p].fa;
                }
            }
        }
    }
}samS, samT;

struct sgt {
    int ls, rs;
    int mx;
}tr[N * 40];
int root[N << 1];
int cnts;

void push_up(int p) {
    tr[p].mx = max(tr[tr[p].ls].mx, tr[tr[p].rs].mx);
}

int add(int p, int pl, int pr, int x) {
    if (!p) {
        p = ++cnts;
    }
    if (pl == pr) {
        tr[p].mx = x;
    } else {
        int mid = (pl + pr) >> 1;
        if (x <= mid) tr[p].ls = add(tr[p].ls, pl, mid, x);
        else tr[p].rs = add(tr[p].rs, mid + 1, pr, x);
        push_up(p);
    }
    return p;
}

int merge(int t1, int t2, int pl, int pr) {
    if (!t1 || !t2) {
        return t1 + t2;
    }
    if (pl == pr) {
        return t1;
    }
    int p = ++cnts;
    int mid = (pl + pr) >> 1;
    tr[p].ls = merge(tr[t1].ls, tr[t2].ls, pl, mid);
    tr[p].rs = merge(tr[t1].rs, tr[t2].rs, mid + 1, pr);
    push_up(p);
    return p;
}

int query(int p, int pl, int pr, int R) {
    if (!p || R < pl) {
        return 0;
    }
    if (tr[p].mx <= R) {
        return tr[p].mx;
    }
    int mid = (pl + pr) >> 1;
    if (R <= mid) {
        return query(tr[p].ls, pl, mid, R);
    }
    int res = query(tr[p].rs, mid + 1, pr, R);
    if (res) {
        return res;
    }
    return tr[tr[p].ls].mx;
}

struct tedge {
    int to, nxt;
}edge[N << 1];
int head[N << 1], cnte;

void addEdge(int u, int v) {
    edge[++cnte].to = v;
    edge[cnte].nxt = head[u];
    head[u] = cnte;
}

void dfs(int u) {
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        dfs(v);
        root[u] = merge(root[u], root[v], 1, n);
    }
}

void build() {
    samS.init();
    for (int i = 1; i <= n; ++i) {
        samS.insert(s[i - 1] - 'a', i);
        int u = samS.np;
        root[u] = add(0, 1, n, i);
    }
    for (int i = 2; i <= samS.tot; ++i) {
        addEdge(samS.tr[i].fa, i);
    }
    dfs(1);
}

void match(int &p, int &len, int c, int l, int r) {
    while (1) {
        int q = samS.tr[p].son[c];
        if (q) {
            int maxpos = query(root[q], 1, n, r);
            int cur = min(len + 1, maxpos - l + 1);
            int minLen = 1;
            if (p != 1) {
                minLen = samS.tr[samS.tr[p].fa].len + 2;
            }
            if (cur >= minLen) {
                p = q;
                len = cur;
                return;
            }
        }
        if (p == 1) {
            len = 0;
            return;
        }
        p = samS.tr[p].fa;
        len = samS.tr[p].len;
    }
}

void init() {
    for (int i = 1; i <= n << 1; ++i) {
        head[i] = 0;
    }
    cnte = cnts = 0;
}

int best[N];

void solve() {
    cin >> s;
    n = s.size();
    init();
    build();

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> t >> l >> r;
        samT.init();
        int m = t.size();
        for (int i = 1, p = 1, len = 0; i <= m; ++i) {
            int c = t[i - 1] - 'a';
            samT.insert(c, i);
            match(p, len, c, l, r);
            best[i] = len;
        }
        i64 ans = 0;
        for (int u = 2; u <= samT.tot; ++u) {
            int lo = samT.tr[samT.tr[u].fa].len;
            int hi = samT.tr[u].len;
            int matched = best[samT.tr[u].pos];
            ans += hi - max(lo, min(hi, matched));
        }
        cout << ans << "\n";
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