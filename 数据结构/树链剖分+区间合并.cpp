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

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;
int arr[N];

struct treeEdge {
    int to, nxt;
}edge[N * 2];
int head[N], cnt = 0;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

struct tree {
    int fa;
    int siz, dep;
    int son;
    int top;
    int dfn;
}tr[N];
int seg[N], cntt = 0;

void dfs1(int u, int fa) {
    tr[u].fa = fa;
    tr[u].siz = 1;
    tr[u].dep = tr[fa].dep + 1;
    tr[u].son = 0;
    int tmp = 0;
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        tr[u].siz += tr[v].siz;
        if (tr[v].siz > tmp) {
            tmp = tr[v].siz;
            tr[u].son = v;
        }
    }
}

void dfs2(int u, int t) {
    tr[u].dfn = ++cntt;
    seg[cntt] = u;
    tr[u].top = t;
    if (!tr[u].son) return;
    dfs2(tr[u].son, t);
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (v == tr[u].son || v == tr[u].fa) continue;
        dfs2(v, v);
    }
}

struct sgt {
    int l, r;
    int df;
    int tag;
}trr[N << 2];

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void push_up(int p) {
    trr[p].df = trr[ls(p)].df + trr[rs(p)].df;
    if (trr[ls(p)].r == trr[rs(p)].l) trr[p].df--;
    trr[p].l = trr[ls(p)].l;
    trr[p].r = trr[rs(p)].r;
}

void build(int p, int pl, int pr) {
    trr[p].tag = 0;
    if (pl == pr) {
        trr[p].df = 1;
        trr[p].l = trr[p].r = arr[seg[pl]];
        return;
    }
    int mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void addtag(int p, int x) {
    trr[p].df = 1;
    trr[p].l = trr[p].r = x;
    trr[p].tag = x;
}

void push_down(int p) {
    if (trr[p].tag) {
        addtag(ls(p), trr[p].tag);
        addtag(rs(p), trr[p].tag);
        trr[p].tag = 0;
    }
}

void update(int p, int pl, int pr, int L, int R, int x) {
    if (L <= pl && pr <= R) {
        addtag(p, x);
        return;
    }
    push_down(p);
    int mid = (pl + pr) >> 1;
    if (L <= mid) update(ls(p), pl, mid, L, R, x);
    if (R > mid) update(rs(p), mid + 1, pr, L, R, x);
    push_up(p);
}

struct node {
    int df;
    int l, r;
};
node operator+ (const node &a, const node &b) {
    node res;
    res.df = a.df + b.df;
    if (a.r == b.l) res.df--;
    res.l = a.l; res.r = b.r;
    return res;
}

node query(int p, int pl, int pr, int L, int R) {
    if (L <= pl && pr <= R) {
        return { trr[p].df, trr[p].l, trr[p].r };
    }
    push_down(p);
    int mid = (pl + pr) >> 1;
    if (L > mid) return query(rs(p), mid + 1, pr, L, R);
    if (R <= mid) return query(ls(p), pl, mid, L, R);
    node n1 = query(ls(p), pl, mid, L, R);
    node n2 = query(rs(p), mid + 1, pr, L, R);
    return n1 + n2;
}

void pathChange(int a, int b, int c) {
    while (tr[a].top != tr[b].top) {
        if (tr[tr[a].top].dep < tr[tr[b].top].dep) {
            update(1, 1, n, tr[tr[b].top].dfn, tr[b].dfn, c);
            b = tr[tr[b].top].fa;
        } else {
            update(1, 1, n, tr[tr[a].top].dfn, tr[a].dfn, c);
            a = tr[tr[a].top].fa;
        }
    }
    update(1, 1, n, min(tr[a].dfn, tr[b].dfn), max(tr[a].dfn, tr[b].dfn), c);
}

node pathQuery(int a, int b) {
    node res1; bool jdg1 = 1;
    node res2; bool jdg2 = 1;
    while (tr[a].top != tr[b].top) {
        if (tr[tr[a].top].dep < tr[tr[b].top].dep) {
            if (jdg1) {
                res1 = query(1, 1, n, tr[tr[b].top].dfn, tr[b].dfn);
                jdg1 = 0;
            } else {
                res1 = query(1, 1, n, tr[tr[b].top].dfn, tr[b].dfn) + res1;
            }
            b = tr[tr[b].top].fa;
        } else {
            if (jdg2) {
                res2 = query(1, 1, n, tr[tr[a].top].dfn, tr[a].dfn);
                jdg2 = 0;
            } else {
                res2 = query(1, 1, n, tr[tr[a].top].dfn, tr[a].dfn) + res2;
            }
            a = tr[tr[a].top].fa;
        }
    }
    node mid = query(1, 1, n, min(tr[a].dfn, tr[b].dfn), max(tr[a].dfn, tr[b].dfn));
    if (tr[a].dep > tr[b].dep) {
        swap(mid.l, mid.r);
    }
    if (!jdg2) {
        swap(res2.l, res2. r);
        mid = res2 + mid;
    }
    if (!jdg1) {
        mid = mid + res1;
    }
    return mid;
}

void init() {
    rep(i, 0, n) {
        head[i] = 0;
    }
    cnt = 0;
    cntt = 0;
}

void solve() {
    cin >> n >> m;
    rep(i, 1, n) {
        cin >> arr[i];
    }
    rep(i, 2, n) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'C') {
            int c;
            cin >> c;
            pathChange(a, b, c);
        } else {
            node ans = pathQuery(a, b);
            cout << ans.df << "\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}