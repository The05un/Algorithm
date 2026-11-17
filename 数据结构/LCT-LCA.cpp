#include<bits/stdc++.h>
using namespace std;

#define debug(x) cout << #x" = " << (x) << endl;
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
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;

struct Splay {
    int fa;
    int ls, rs;
    int rev;
}tr[N];

bool isroot(int x) {
    return tr[tr[x].fa].ls != x && tr[tr[x].fa].rs != x;
}

bool lr(int x) {
    return tr[tr[x].fa].rs == x ? 1 : 0;
}

void rev(int x) {
    if (x) {
        swap(tr[x].ls, tr[x].rs);
        tr[x].rev ^= 1;
    }
}

void down(int x) {
    if (tr[x].rev) {
        rev(tr[x].ls);
        rev(tr[x].rs);
        tr[x].rev ^= 1;
    }
}

void rotate(int x) {
    int f = tr[x].fa, g = tr[f].fa;
    if (lr(x)) {
        tr[f].rs = tr[x].ls;
        if (tr[f].rs) {
            tr[tr[f].rs].fa = f;
        }
        tr[x].ls = f;
    } else {
        tr[f].ls = tr[x].rs;
        if (tr[f].ls) {
            tr[tr[f].ls].fa = f;
        }
        tr[x].rs = f;
    }
    if (!isroot(f)) {
        if (lr(f)) {
            tr[g].rs = x;
        } else {
            tr[g].ls = x;
        }
    }
    tr[x].fa = g;
    tr[f].fa = x;
}

stack<int> st;

void splay(int x) {
    st.push(x);
    for (int y = x; !isroot(y); y = tr[y].fa) {
        st.push(tr[y].fa);
    }
    while (!st.empty()) {
        int t = st.top(); st.pop();
        down(t);
    }
    while (!isroot(x)) {
        int f = tr[x].fa;
        if (!isroot(f)) {
            if (lr(f) == lr(x)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

int acc(int x) {
    int y;
    for (y = 0; x; y = x, x = tr[x].fa) {
        splay(x);
        tr[x].rs = y;
    }
    return y;
}

void makeroot(int x) {
    acc(x);
    splay(x);
    rev(x);
}

int findroot(int x) {
    acc(x);
    splay(x);
    down(x);
    while (tr[x].ls) {
        x = tr[x].ls;
        down(x);
    }
    splay(x);
    return x;
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        tr[x].fa = y;
    }
}

void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && tr[x].rs == y && tr[y].fa == x && tr[y].ls == 0) {
        tr[x].rs = 0;
        tr[y].fa = 0;
    }
}

int lca(int x, int y) {
    if (x == y) return x;
    acc(x);
    return acc(y);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        string op;
        cin >> op;
        if (op == "Connect") {
            int x, y;
            cin >> x >> y;
            link(x, y);
        } else if (op == "Destroy") {
            int x, y;
            cin >> x >> y;
            cut(x, y);
        } else {
            int x, y;
            cin >> x >> y;
            if (findroot(x) == findroot(y)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
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