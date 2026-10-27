#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e5 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;

struct FHQtreap {
    int key;
    int ls;
    int rs;
    int siz;
    f64 priority;
}tr[N];
int head = 0, cnt = 0;

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        tr[l].rs = tr[r].ls = 0;
    } else {
        if (tr[i].key <= num) {
            tr[l].rs = i;
            split(i, r, tr[i].rs, num);
        } else {
            tr[r].ls = i;
            split(l, i, tr[i].ls, num);
        }
        up(i);
    }
}

void splitByRank(int l, int r, int i, int rank) {
    if (i == 0) {
        tr[l].rs = tr[r].ls = 0;
    } else {
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
        tr[l].rs = merge(tr[l].rs, r);
        up(l);
        return l;
    } else {
        tr[r].ls = merge(l, tr[r].ls);
        up(r);
        return r;
    }
}

void add(int num) {
    split(0, 0, head, num);
    tr[++cnt].key = num;
    tr[cnt].siz = 1;
    tr[cnt].priority = (double)rand() / RAND_MAX;
    head = merge(merge(tr[0].rs, cnt), tr[0].ls);
}

void reMove(int num) {
    split(0, 0, head, num);
    int lm = tr[0].rs;
    int r = tr[0].ls;
    split(0, 0, lm, num - 1);
    int l = tr[0].rs;
    int m = tr[0].ls;
    if (m != 0) {
        m = merge(tr[m].ls, tr[m].rs);
    }
    head = merge(merge(l, m), r);
}

int getRank(int num) {
    split(0, 0, head, num - 1);
    int ans = tr[tr[0].rs].siz + 1;
    head = merge(tr[0].rs, tr[0].ls);
    return ans;
}

int index(int i, int x) {
    if (tr[tr[i].ls].siz >= x) {
        return index(tr[i].ls, x);
    } else if (tr[tr[i].ls].siz + 1 < x) {
        return index(tr[i].rs, x - (tr[tr[i].ls].siz + 1));
    } else {
        return tr[i].key;
    }
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (tr[i].key >= num) {
        return pre(tr[i].ls, num);
    } else {
        return max(tr[i].key, pre(tr[i].rs, num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (tr[i].key <= num) {
        return post(tr[i].rs, num);
    } else {
        return min(tr[i].key, post(tr[i].ls, num));
    }
}

int post(int num) {
    return post(head, num);
}

int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            reMove(x);
        } else if (op == 3) {
            cout << getRank(x) << "\n";
        } else if (op == 4) {
            cout << index(x) << "\n";
        } else if (op == 5) {
            cout << pre(x) << "\n";
        } else {
            cout << post(x) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
