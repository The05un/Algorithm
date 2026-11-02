#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 2e5 + 5;
const int M = 100 + 5;
const int mod = 998244353;
const int INF = -1e9 - 7;
const f64 gama = 1e-9;

i64 n;

i64 rec[N][4];
struct line1 {
    i64 x;
    i64 y1, y2;
    i64 op;
    bool operator< (const line1 &other) const {
        return x < other.x;
    }
}line[N];
i64 ysort[N];

struct sgt {
    i64 length;
    i64 cover;
    i64 times;
}tr[N << 2];

i64 prepare(i64 n) {
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

void build(i64 p, i64 pl, i64 pr) {
    if (pl < pr) {
        i64 mid = (pl + pr) >> 1;
        build(ls(p), pl, mid);
        build(rs(p), mid + 1, pr);
    }
    tr[p].length = ysort[pr + 1] - ysort[pl];
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
        ysort[i] = y1; ysort[j] = y2;
        line[i].x = x1; line[i].y1 = y1; line[i].y2 = y2; line[i].op = 1; 
        line[j].x = x2; line[j].y1 = y1; line[j].y2 = y2; line[j].op = -1; 
    }
    n <<= 1;
    i64 m = prepare(n);
    build(1, 1, m);
    sort(line + 1, line + n + 1);
    i64 ans = 0;
    for (i64 i = 1, pre = 0; i <= n; ++i) {
        ans += tr[1].cover * (line[i].x - pre);
        pre = line[i].x;
        add(1, 1, m, rank1(line[i].y1, m), rank1(line[i].y2, m) - 1, line[i].op);
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
