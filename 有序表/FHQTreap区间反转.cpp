#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 2e6 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;

struct FHQtreap {
    int key;
    int ls;
    int rs;
    int siz;
    f64 priority;
    int rev;
}tr[N];
int head = 0, cnt = 0;
int ansi;
int ans[N];

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + 1;
}

void down(int i) {
    if (tr[i].rev) {
        swap(tr[i].ls, tr[i].rs);
        tr[tr[i].ls].rev ^= 1;
        tr[tr[i].rs].rev ^= 1;
        tr[i].rev = 0;
    }
}

void splitByRank(int l, int r, int i, int rank) {
    if (i == 0) {
        tr[l].rs = tr[r].ls = 0;
    } else {
        down(i);
        if (tr[tr[i].ls].siz + 1 <= rank) {
            tr[l].rs = i;
            splitByRank(i, r, tr[i].rs, rank - tr[tr[i].ls].siz - 1);
        } else {
            tr[r].ls = i;
            splitByRank(l, i, tr[i].ls, rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (tr[l].priority >= tr[r].priority) {
        down(l);
        tr[l].rs = merge(tr[l].rs, r);
        up(l);
        return l;
    } else {
        down(r);
        tr[r].ls = merge(l, tr[r].ls);
        up(r);
        return r;
    }
}

void inOrder(int i) {
    if (!i) return;
    down(i);
    inOrder(tr[i].ls);
    ans[++ansi] = tr[i].key;
    inOrder(tr[i].rs);
}

int n, m;

void solve() {
    srand(time(0));
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        tr[++cnt].key = i;
        tr[cnt].ls = tr[cnt].rs = tr[cnt].rev = 0;
        tr[cnt].siz = 1;
        tr[cnt].priority = (double)rand() / RAND_MAX;
        head = merge(head, cnt);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        splitByRank(0, 0, head, a - 1);
        int l = tr[0].rs;
        int rm = tr[0].ls;
        splitByRank(0, 0, rm, b - a + 1);
        int m = tr[0].rs;
        int r = tr[0].ls;
        tr[m].rev ^= 1;
        head = merge(merge(l, m), r);
    }
    inOrder(head);
    for (int i = 1; i <= ansi; ++i) {
        cout << ans[i] << " ";
    }cout << "\n";
}


int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
