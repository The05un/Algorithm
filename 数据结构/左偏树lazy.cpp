#include<bits/stdc++.h>
using namespace std;

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define Rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define Dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
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

const int N = 3e5 + 5;
const int M = 1000 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;

struct att {
    int s, c;
    int ls, rs;
    int dist;
    int add, mul;
}tr[N];

struct def {
    int de;
    int f, a, v;
    int cnt;
}city[N];

int top[N];
int deep[N];
int ans[N];

void prepare() {
    tr[0].dist = -1;
    Rep(i, 1, m) {
        tr[i].dist = tr[i].ls = tr[i].rs = 0;
        tr[i].add = 0;
        tr[i].mul = 1;
        ans[i] = -1;
    }
    Rep(i, 1, n) {
        top[i] = city[i].cnt = 0;
    }
}

void upgrade(int i, int t, int v) {
    if (t == 0) {
        tr[i].s += v;
        tr[i].add += v;
    } else {
        tr[i].s *= v;
        tr[i].mul *= v;
        tr[i].add *= v;
    }
}

void down(int i) {
    if (tr[i].mul == 1 && tr[i].add == 0) {
        return;
    }
    int l = tr[i].ls;
    int r = tr[i].rs;
    if (l) {
        tr[l].s = tr[l].s * tr[i].mul + tr[i].add;
        tr[l].add = tr[l].add * tr[i].mul + tr[i].add;
        tr[l].mul *= tr[i].mul;
    }
    if (r) {
        tr[r].s = tr[r].s * tr[i].mul + tr[i].add;
        tr[r].add = tr[r].add * tr[i].mul + tr[i].add;
        tr[r].mul *= tr[i].mul;
    }
    tr[i].add = 0;
    tr[i].mul = 1;
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return (i + j);
    }
    if (tr[i].s > tr[j].s || (tr[i].s == tr[j].s && i > j)) {
        swap(i, j);
    }
    down(i);
    tr[i].rs = merge(tr[i].rs, j);
    if (tr[tr[i].ls].dist < tr[tr[i].rs].dist) {
        swap(tr[i].ls, tr[i].rs);
    }
    tr[i].dist = tr[tr[i].rs].dist + 1;
    return i;
}

int pop(int i) {
    down(i);
    int ans = merge(tr[i].ls, tr[i].rs);
    tr[i].ls = tr[i].rs = tr[i].dist = 0;
    return ans;
}

void compute() {
    deep[1] = 1;
    Rep(i, 2, n) {
        deep[i] = deep[city[i].f] + 1;
    }
    Rep(i, 1, m) {
        if (top[tr[i].c] == 0) {
            top[tr[i].c] = i;
        } else {
            top[tr[i].c] = merge(top[tr[i].c], i);
        }
    }
    Dep(i, n, 1) {
        while (top[i] != 0 && tr[top[i]].s < city[i].de) {
            city[i].cnt++;
            ans[top[i]] = deep[tr[top[i]].c] - deep[i];
            top[i] = pop(top[i]);
        }
        if (top[i] != 0) {
            upgrade(top[i], city[i].a, city[i].v);
            if (top[city[i].f] == 0) {
                top[city[i].f] = top[i];
            } else {
                top[city[i].f] = merge(top[i], top[city[i].f]);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    prepare();
    Rep(i, 1, n) {
        cin >> city[i].de;
    }
    Rep(i, 2, n) {
        cin >> city[i].f >> city[i].a >> city[i].v;
    }
    Rep(i, 1, m) {
        cin >> tr[i].s >> tr[i].c;
    }
    compute();
    Rep(i, 1, n) {
        cout << city[i].cnt << "\n";
    }
    Rep(i, 1, m) {
        if (ans[i] == -1) {
            ans[i] = deep[tr[i].c];
        }
        cout << ans[i] << "\n";
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