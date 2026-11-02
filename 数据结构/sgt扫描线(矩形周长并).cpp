#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = double;

const int N = 5e5 + 5;
const int M = 1000 + 5;
const int mod = 1e9 + 7;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

i64 n;
i64 rec[N][4];

struct line1 {
    i64 x;
    i64 y1, y2;
    i64 op;
    bool operator< (const line1 &other) const {
        if (x != other.x) {
            return x < other.x;
        } else {
            return op > other.op;
        }
    }
}linex[N];
i64 ysort[N];

struct line2 {
    i64 y;
    i64 x1, x2;
    i64 op;
    bool operator< (const line2 &other) const {
        if (y != other.y) {
            return y < other.y;
        } else {
            return op > other.op;
        }
    }
}liney[N];
i64 xsort[N];

struct sgt {
    i64 length;
    i64 cover;
    i64 times;
}tr[N << 2];

i64 prepare1(i64 n) {
    sort(ysort + 1, ysort + n + 1);
    i64 m = 1;
    for (i64 i = 2; i <= n; ++i) {
        if (ysort[m] != ysort[i]) {
            ysort[++m] = ysort[i];
        }
    }
    ysort[m + 1] = ysort[m];
    return m;
}

i64 prepare2(i64 n) {
    sort(xsort + 1, xsort + n + 1);
    i64 m = 1;
    for (i64 i = 2; i <= n; ++i) {
        if (xsort[m] != xsort[i]) {
            xsort[++m] = xsort[i];
        }
    }
    xsort[m + 1] = xsort[m];
    return m;
}

i64 rank1(i64 num, i64 n) {
    i64 l = 0, r = n + 1, mid;
    while (l + 1 < r) {
        mid = (l + r) >> 1;
        if (ysort[mid] >= num) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

i64 rank2(i64 num, i64 n) {
    i64 l = 0, r = n + 1, mid;
    while (l + 1 < r) {
        mid = (l + r) >> 1;
        if (xsort[mid] >= num) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

i64 ls(i64 p) { return p << 1; };
i64 rs(i64 p) { return p << 1 | 1; }

void push_up(i64 p, i64 pl, i64 pr) {
    if (tr[p].times) {
        tr[p].cover = tr[p].length;
    } else if (pl == pr) {
        tr[p].cover = 0;
    } else {
        tr[p].cover = tr[ls(p)].cover + tr[rs(p)].cover;
    }
}

void build1(i64 p, i64 pl, i64 pr) {
    if (pl < pr) {
        i64 mid = (pl + pr) >> 1;
        build1(ls(p), pl, mid);
        build1(rs(p), mid + 1, pr);
    }
    tr[p].length = ysort[pr + 1] - ysort[pl];
    tr[p].times = 0;
    tr[p].cover = 0;
}

void build2(i64 p, i64 pl, i64 pr) {
    if (pl < pr) {
        i64 mid = (pl + pr) >> 1;
        build2(ls(p), pl, mid);
        build2(rs(p), mid + 1, pr);
    }
    tr[p].length = xsort[pr + 1] - xsort[pl];
    tr[p].times = 0;
    tr[p].cover = 0;
}

void add(i64 p, i64 pl, i64 pr, i64 L, i64 R, i64 x) {
    if (L <= pl && pr <= R) {
        tr[p].times += x;
    } else {
        i64 mid = (pl + pr) >> 1;
        if (L <= mid) add(ls(p), pl, mid, L, R, x);
        if (R > mid) add(rs(p), mid + 1, pr, L, R, x);
    }
    push_up(p, pl, pr);
}

i64 compute() {
    for (i64 i = 1, j = n + 1, x1, y1, x2, y2; i <= n; ++i, ++j) {
        x1 = rec[i][0]; y1 = rec[i][1]; x2 = rec[i][2]; y2 = rec[i][3];
        xsort[i] = x1; xsort[j] = x2;
        ysort[i] = y1; ysort[j] = y2;
        linex[i].x = x1; linex[i].y1 = y1; linex[i].y2 = y2; linex[i].op = 1; 
        linex[j].x = x2; linex[j].y1 = y1; linex[j].y2 = y2; linex[j].op = -1; 
        liney[i].y = y1; liney[i].x1 = x1; liney[i].x2 = x2; liney[i].op = 1; 
        liney[j].y = y2; liney[j].x1 = x1; liney[j].x2 = x2; liney[j].op = -1; 
    }
    n <<= 1;
    i64 ans = 0;
    i64 m1 = prepare1(n);
    build1(1, 1, m1);
    sort(linex + 1, linex + n + 1);
    for (i64 i = 1, pre = 0; i <= n; ++i) {
        pre = tr[1].cover;
        add(1, 1, m1, rank1(linex[i].y1, m1), rank1(linex[i].y2, m1) - 1, linex[i].op);
        ans += abs(tr[1].cover - pre);
    }
    i64 m2 = prepare2(n);
    build2(1, 1, m2);
    sort(liney + 1, liney + n + 1);
    for (i64 i = 1, pre = 0; i <= n; ++i) {
        pre = tr[1].cover;
        add(1, 1, m2, rank2(liney[i].x1, m2), rank2(liney[i].x2, m2) - 1, liney[i].op);
        ans += abs(tr[1].cover - pre);
    }
    return ans;
}

void solve() {
    cin >> n;
    for (i64 i = 1; i <= n; ++i) {
        cin >> rec[i][0] >> rec[i][1];
        cin >> rec[i][2] >> rec[i][3];
    }
    cout << compute() << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}