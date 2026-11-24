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

const int N = 1e6 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n;
string s;
i64 ans;

struct SAM {
    int son[26];
    int fa;
    int len;
    int cnt;
}tr[N << 1];
int tot, np;

void insert(int c) {
    int p = np;
    np = ++tot;
    tr[np].len = tr[p].len + 1;
    tr[np].cnt = 1;

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
            tr[nq].len = tr[p].len + 1;
            tr[nq].fa = tr[q].fa;
            tr[q].fa = nq;
            tr[np].fa = nq;
            while (p && tr[p].son[c] == q) {
                tr[p].son[c] = nq;
                p = tr[p].fa;
            }
            memcpy(tr[nq].son, tr[q].son, sizeof(tr[q].son));
        }
    }

}

struct tedge {
    int to, nxt;
}edge[N << 1];
int head[N << 1], cnt;

void addEdge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int u) {
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        dfs(v);
        tr[u].cnt += tr[v].cnt;
    }
    if (tr[u].cnt > 1) ans = max(ans, 1LL * tr[u].cnt * tr[u].len);
}

void init() {
    for (int i = 0; i <= n << 1; ++i) {
        head[i] = 0;
        tr[i] = SAM{};
    }
    cnt = 0;
    tot = np = 1;
    ans = 0;
}

void solve() {
    cin >> s;
    n = s.size();
    init();
    for (int i = 0; i < n; ++i) {
        int ch = s[i] - 'a';
        insert(ch);
    }
    for (int i = 2; i <= tot; ++i) {
        addEdge(tr[i].fa, i);
    }
    dfs(1);
    cout << ans << "\n";
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