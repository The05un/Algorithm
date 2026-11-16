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
const int M = 400 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n;

int over[N];
int tr[N][26], cnt;
int fail[N];

void insert(int i, const string &s) {
    int u = 0;
    int sz = s.length();
    for (int j = 0; j < sz; ++j) {
        int ch = s[j] - 'a';
        if (!tr[u][ch]) {
            tr[u][ch] = ++cnt;
        }
        u = tr[u][ch];
    }
    over[i] = u;
}

queue<int> q;

void setFail() {
    while (!q.empty()) q.pop();
    for (int i = 0; i <= 25; ++i) {
        if (tr[0][i] > 0) {
            q.push(tr[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i <= 25; ++i) {
            if (tr[u][i] == 0) {
                tr[u][i] = tr[fail[u]][i];
            } else {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            }
        }
    }
}

struct edg {
    int to, nxt;
}edge[N];
int head[N], cnte;

void addEdge(int u, int v) {
    edge[++cnte].to = v;
    edge[cnte].nxt = head[u];
    head[u] = cnte;
} 

int times[N];

void f1(int u) {
    for (int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        f1(v);
        times[u] += times[v];
    }
}

void init() {
    for (int i = 0; i <= cnt; ++i) {
        memset(tr[i], 0, sizeof(tr[i]));
        fail[i] = times[i] = head[i] = 0;
    }
    cnt = cnte = 0;
}

void solve() {
    cin >> n;
    init();
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        insert(i, s);
    }
    setFail();
    string text;
    cin >> text;
    int sz = text.size();
    int u = 0;
    for (int i = 0; i < sz; ++i) {
        int ch = text[i] - 'a';
        u = tr[u][ch];
        times[u]++;
    }
    for (int i = 1; i <= cnt; ++i) {
        addEdge(fail[i], i);
    }
    f1(0);
    for (int i = 1; i <= n; ++i) {
        cout << times[over[i]] << "\n";
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