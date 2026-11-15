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
const int M = 400 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, m;
int arr[N];

struct splayTree {
    int fa;
    int ls, rs;
    int rev;
    int xorsum;
}tr[N];

void up(int x) {
    tr[x].xorsum = tr[tr[x].ls].xorsum ^ tr[tr[x].rs].xorsum ^ arr[x];
}

bool isroot(int x) {
    return tr[tr[x].fa].ls != x && tr[tr[x].fa].rs != x;
}

int lr(int x) {
    return tr[tr[x].fa].ls == x ? 0 : 1;
}

void rev(int x) {
    if (x != 0) {
        int tmp = tr[x].ls;
        tr[x].ls = tr[x].rs;
        tr[x].rs = tmp;
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
    if (lr(x) == 0) {
        tr[f].ls = tr[x].rs;
        if (tr[f].ls != 0) {
            tr[tr[f].ls].fa = f;
        }
        tr[x].rs = f;
    } else {
        tr[f].rs = tr[x].ls;
        if (tr[f].rs != 0) {
            tr[tr[f].rs].fa = f;
        }
        tr[x].ls = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            tr[g].ls = x;
        } else {
            tr[g].rs = x;
        }
    }
    tr[f].fa = x;
    tr[x].fa = g;
    up(f);
    up(x);
}

int sta[N], siz;

void splay(int x) {
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = tr[y].fa) {
        sta[++siz] = tr[y].fa;
    }
    while (siz != 0) {
        down(sta[siz--]);
    }
    while (!isroot(x)) {
        int f = tr[x].fa;
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

void acc(int x) {
    for (int y = 0; x != 0; y = x, x = tr[x].fa) {
        splay(x);
        tr[x].rs = y;
        up(x);
    }
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
    while (tr[x].ls != 0) {
        x = tr[x].ls;
        down(x);
    }
    splay(x);
    return x;
}

void split(int x, int y) {
    makeroot(x);
    acc(y);
    splay(y);
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        tr[x].fa = y;
    }
}

void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && tr[y].fa == x && tr[y].ls == 0 && tr[x].rs == y) {
        tr[y].fa = tr[x].rs = 0;
        up(x);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        tr[i].xorsum = arr[i];
    }
    for (int i = 1; i <= m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            split(x, y);
            cout << tr[y].xorsum << "\n";
        } else if (op == 1) {
            link(x, y);
        } else if (op == 2) {
            cut(x, y);
        } else {
            splay(x);
            arr[x] = y;
            up(x);
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