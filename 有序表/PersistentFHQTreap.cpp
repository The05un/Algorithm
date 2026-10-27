#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 5e5 + 5;
const int M = 100 + 5;
const int mod = 1e9 + 7;

struct PersistentFHQTreap {
    int key;
    int ls;
    int rs;
    int siz;
    f64 priority;
}tr[N * 50];
int head[N], cnt = 0;

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + 1;
}

int copy(int i) {
    tr[++cnt] = tr[i];
    return cnt;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        tr[l].rs = tr[r].ls = 0;
    } else {
        i = copy(i);
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
        i = copy(i);
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
        l = copy(l);
        tr[l].rs = merge(tr[l].rs, r);
        up(l);
        return l;
    } else {
        r = copy(r);
        tr[r].ls = merge(l, tr[r].ls);
        up(r);
        return r;
    }
}

void add(int v, int i, int num) {
    split(0, 0, i, num);
    int l = tr[0].rs;
    int r = tr[0].ls;
    tr[0].ls = tr[0].rs = 0;
    tr[++cnt].key = num;
    tr[cnt].siz = 1;
    tr[cnt].priority = (double)rand() / RAND_MAX;
    head[v] = merge(merge(l, cnt), r);
}

void reMove(int v, int i, int num) {
    split(0, 0, i, num);
    int lm = tr[0].rs;
    int r = tr[0].ls;
    split(0, 0, lm, num - 1);
    int l = tr[0].rs;
    int m = tr[0].ls;
    tr[0].ls = tr[0].rs = 0;
    if (m != 0) {
        m = merge(tr[m].ls, tr[m].rs);
    }
    head[v] = merge(merge(l, m), r);
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (tr[i].key >= num) {
        return small(tr[i].ls, num);
    } else {
        return small(tr[i].rs, num) + tr[tr[i].ls].siz + 1;
    }
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


int n;

void solve() {
    srand(time(0));
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int v, op, x;
        cin >> v >> op >> x;
        if (op == 1) {
            add(i, head[v], x);
        } else if (op == 2) {
            reMove(i, head[v], x);
        } else {
            head[i] = head[v];
            if (op == 3) {
                cout << small(head[i], x) + 1 << "\n";
            } else if (op == 4) {
                cout << index(head[i], x) << "\n";
            } else if (op == 5) {
                cout << pre(head[i], x) << "\n";
            } else {
                cout << post(head[i], x) << "\n";
            }
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
