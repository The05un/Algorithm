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

const int N = 1301 + 5;
const int M = 2000 + 5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

string s;
int n, m;

int tr[M][10], cnt;
int fail[M];
int alert[M];

void insert(const string &s) {
    int u = 0;
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int ch = s[i]  - '0';
        if (!tr[u][ch]) {
            tr[u][ch] = ++cnt;
        }
        u = tr[u][ch];
    }
    alert[u] = 1;
}

queue<int> q;

void setFail() {
    while (!q.empty()) q.pop();
    for (int i = 0; i <= 9; ++i) {
        if (tr[0][i]) {
            q.push(tr[0][i]);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i <= 9; ++i) {
            if (!tr[u][i]) {
                tr[u][i] = tr[fail[u]][i];
            } else {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            }
        }
        alert[u] |= alert[fail[u]];
    }
}

int dp[N][M][2][2];

int f(int i, int j, int free, int has) {
    if (alert[j]) {
        return 0;
    }
    if (i == n) {
        return has;
    }
    if (dp[i][j][free][has] != -1) {
        return dp[i][j][free][has];
    }
    int ans = 0;
    int cur = s[i] - '0';
    if (has == 0) {
        if (free == 0) {
            ans = (ans + f(i + 1, 0, 1, 0)) % mod;
            for (int pic = 1; pic < cur; pic++) {
                ans = (ans + f(i + 1, tr[j][pic], 1, 1)) % mod;
            }
            ans = (ans + f(i + 1, tr[j][cur], 0, 1)) % mod;
        } else {
            ans = (ans + f(i + 1, 0, 1, 0)) % mod;
            for (int pic = 1; pic <= 9; ++pic) {
                ans = (ans + f(i + 1, tr[j][pic], 1, 1)) % mod;
            }
        }
    } else {
        if (free == 0) {
            for (int pic = 0; pic < cur; pic++) {
                ans = (ans + f(i + 1, tr[j][pic], 1, 1)) % mod;
            }
            ans = (ans + f(i + 1, tr[j][cur], 0, 1)) % mod;
        } else {
            for (int pic = 0; pic <= 9; ++pic) {
                ans = (ans + f(i + 1, tr[j][pic], 1, 1)) % mod;
            }
        }
    }
    dp[i][j][free][has] = ans;
    return ans;
}

void clean() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= cnt; ++j) {
            dp[i][j][0][0] = -1;
            dp[i][j][1][0] = -1;
            dp[i][j][0][1] = -1;
            dp[i][j][1][1] = -1;
        }
    }
}

void init() {
    cnt = 0;
}

void solve() {
    cin >> s;
    n = s.size();
    init();
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        string p;
        cin >> p;
        insert(p);
    }
    setFail();
    clean();
    cout << f(0, 0, 0, 0) << "\n";
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