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
const int mod = 1e9 + 7;

int n;

int cntn;
int root;
struct scapeGoat {
    int key;
    int ls;
    int rs;
    bool alive;
    int aliveSiz;
}tr[N];
f64 ALPHA = 0.7;
int top;
int father;
int side;
int collect[N];
int collectSiz;

int init(int num) {
    tr[++cntn].key = num;
    tr[cntn].ls = tr[cntn].rs = 0;
    tr[cntn].alive = 1;
    tr[cntn].aliveSiz = 1;
    return cntn;
}

void up(int i) {
    tr[i].aliveSiz = (tr[i].alive ? 1 : 0) + tr[tr[i].ls].aliveSiz + tr[tr[i].rs].aliveSiz;
}

void inOrder(int i) {
    if (i != 0 && tr[i].aliveSiz != 0) {
        inOrder(tr[i].ls);
        if (tr[i].alive) {
            collect[++collectSiz] = i;
        }
        inOrder(tr[i].rs);
    }
}

int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int m = (l + r) >> 1;
    int h = collect[m];
    tr[h].ls = build(l, m - 1);
    tr[h].rs = build(m + 1, r);
    up(h);
    return h;
}

void rebuild() {
    if (top != 0) {
        collectSiz = 0;
        inOrder(top);
        int newRoot = build(1, collectSiz);
        if (father == 0) {
            root = newRoot;
        } else if (side == 1) {
            tr[father].ls = newRoot;
        } else {
            tr[father].rs = newRoot;
        }
    }
}

bool balance(int i) {
    return ALPHA * tr[i].aliveSiz >= max(tr[tr[i].ls].aliveSiz, tr[tr[i].rs].aliveSiz);
}

int add(int i, int f, int s, int num) {
    if (i == 0 || tr[i].aliveSiz == 0) {
        return init(num);
    }
    if (num <= tr[i].key) {
        tr[i].ls = add(tr[i].ls, i, 1, num);
    } else {
        tr[i].rs = add(tr[i].rs, i, 2, num);
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
    return i;
}

void add(int num) {
    top = father = side = 0;
    root = add(root, 0, 0, num);
    rebuild();
}

int small(int i, int num) {
    if (i == 0 || tr[i].aliveSiz == 0) {
        return 0;
    }
    if (num <= tr[i].key) {
        return small(tr[i].ls, num);
    } else {
        return tr[tr[i].ls].aliveSiz + (tr[i].alive ? 1 : 0) + small(tr[i].rs, num);
    }
}

int getRank(int num) {
    return small(root, num) + 1;
}

int index(int i, int x) {
    if (x <= tr[tr[i].ls].aliveSiz) {
        return index(tr[i].ls, x);
    } else {
        int less = tr[tr[i].ls].aliveSiz + (tr[i].alive ? 1 : 0);
        if (less < x) {
            return index(tr[i].rs, x - less);
        }
    }
    return tr[i].key;
}

int index(int x) {
    return index(root, x);
}

int pre(int num) {
    int kth = getRank(num);
    if (kth == 1) {
        return INT_MIN;
    } else {
        return index(kth - 1);
    }
}

int post(int num) {
    int kth = getRank(num + 1);
    if (kth == tr[root].aliveSiz + 1) {
        return INT_MAX;
    } else {
        return index(kth);
    }
}

void remove(int i, int f, int s, int rank) {
    int lsiz = tr[tr[i].ls].aliveSiz;
    if (rank <= lsiz) {
        remove(tr[i].ls, i, 1, rank);
    } else {
        int cur = tr[i].alive ? 1 : 0;
        if (tr[i].alive && rank == lsiz + cur) {
            tr[i].alive = 0;
        } else {
            remove(tr[i].rs, i, 2, rank - lsiz - cur);
        }
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
}

void remove(int num) {
    int rank1 = getRank(num);
    int rank2 = getRank(num + 1);
    if (rank1 != rank2) {
        top = father = side = 0;
        remove(root, 0, 0, rank1);
        rebuild();
    }
}


void solve() {
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << "\n";
        } else if (op == 4) {
            cout << index(x) << "\n";
        } else if (op == 5) {
            cout << pre(x) << "\n";
        } else if (op == 6) {
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