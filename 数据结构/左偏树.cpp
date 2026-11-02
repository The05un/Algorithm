#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = double;

const i64 N = 2e6 + 5;
const i64 M = 1000 + 5;
const i64 mod = 1e9 + 7;
const i64 INF = -1e9 - 7;
const f64 gama = 1e-9;

i64 W, K;
i64 n, m;

struct LeftistHeap {
    i64 num;
    i64 up, ls, rs;
    i64 dist;
}tr[N];
i64 fa[N];

void prepare() {
    tr[0].dist = -1;
    for (i64 i = 1; i <= n; ++i) {
        tr[i].up = tr[i].ls = tr[i].rs = tr[i].dist = 0;
        fa[i] = i;
    }
}

i64 find(i64 i) {
    return fa[i] == i ? i : (fa[i] = find(fa[i]));
}

i64 merge(i64 i, i64 j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (tr[i].num < tr[j].num || (tr[i].num == tr[j].num && i > j)) {
        swap(i, j);
    }
    tr[i].rs = merge(tr[i].rs, j);
    tr[tr[i].rs].up = i;
    if (tr[tr[i].ls].dist < tr[tr[i].rs].dist) {
        swap(tr[i].ls, tr[i].rs);
    }
    tr[i].dist = tr[tr[i].rs].dist + 1;
    fa[tr[i].ls] = fa[tr[i].rs] = i;
    return i;
}

i64 remove(i64 i) {
    i64 h = find(i);
    fa[tr[i].ls] = tr[i].ls;
    fa[tr[i].rs] = tr[i].rs;
    i64 s = merge(tr[i].ls, tr[i].rs);
    i64 f = tr[i].up;
    fa[i] = s;
    tr[s].up = f;
    if (h != i) {
        fa[s] = h;
        if (tr[f].ls == i) {
            tr[f].ls = s;
        } else {
            tr[f].rs = s;
        }
        for (i64 d = tr[s].dist; tr[f].dist > d + 1; f = tr[f].up, d++) {
            tr[f].dist = d + 1;
            if (tr[tr[f].ls].dist < tr[tr[f].rs].dist) {
                swap(tr[f].ls, tr[f].rs);
            }
        }
    }
    tr[i].up = tr[i].ls = tr[i].rs = tr[i].dist = 0;
    return fa[s];
}

void reduce(i64 i, i64 v) {
    i64 h = remove(i);
    tr[i].num = max(tr[i].num - v, 0LL);
    fa[h] = fa[i] = merge(h, i);
}

i64 compute() {
    i64 ans = 0;
    i64 mx = 0;
    for (i64 i = 1; i <= n; ++i) {
        if (fa[i] == i) {
            ans += tr[i].num;
            if (tr[i].num > mx) mx = tr[i].num;
        }
    }
    if (W == 2) {
        ans -= mx;
    } else if (W == 3) {
        ans += mx;
    }
    return ans;
}

void solve() {
    cin >> n >> m;
    prepare();
    for (i64 i = 1; i <= n; ++i) {
        cin >> tr[i].num;
    }
    while (m--) {
        i64 op;
        cin >> op;
        if (op == 2) {
            i64 a;
            cin >> a;
            reduce(a, tr[a].num);
        } else if (op == 3) {
            i64 a, b;
            cin >> a >> b;
            int l = find(a);
            reduce(l, b);
        } else {
            i64 a, b;
            cin >> a >> b;
            i64 l = find(a);
            i64 r = find(b);
            if (l != r) {
                merge(l, r);
            }
        }
    }
    i64 res = compute();
    if (res == 0) {
        cout << "Gensokyo " << res << "\n";
        return;
    }
    if (res > K) {
        cout << "Hell " << res << "\n";
    } else {
        cout << "Heaven " << res << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    i64 T = 1; cin >> T >> W >> K;
    while (T--) {
        solve();
    }
    return 0;
}