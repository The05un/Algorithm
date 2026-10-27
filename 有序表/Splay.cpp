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
const int M = 1000 + 5;
const int mod = 1e9 + 7;

int n;

struct Splay {
    int key;
    int fa;
    int ls, rs;
    int siz;
}tr[N];
int head = 0, cnt = 0;

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + 1;
}

int lr(int i) {
    return tr[tr[i].fa].rs == i ? 1 : 0;
}

void rotate(int i) {
    int f = tr[i].fa, g = tr[f].fa, soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        tr[f].rs = tr[i].ls;
        if (tr[f].rs != 0){
            tr[tr[f].rs].fa = f;
        }
        tr[i].ls = f;
    } else {
        tr[f].ls = tr[i].rs;
        if (tr[f].ls != 0) {
            tr[tr[f].ls].fa = f;
        }
        tr[i].rs = f;
    }
    if (g != 0) {
        if (sonf == 1) {
            tr[g].rs = i;
        } else {
            tr[g].ls = i;
        }
    }
    tr[f].fa = i;
    tr[i].fa = g;
    up(f);
    up(i);
}

void splay(int i, int goal) {
    int f = tr[i].fa, g = tr[f].fa;
    while (f != goal) {
        if (g != goal) {
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);
        f = tr[i].fa;
        g = tr[f].fa;
    }
    if (goal == 0) {
        head = i;
    }
}

int find(int rank) {
    int i = head;
    while (i != 0) {
        if (tr[tr[i].ls].siz + 1 == rank) {
            return i;
        } else if (tr[tr[i].ls].siz >= rank) {
            i = tr[i].ls;
        } else {
            rank -= tr[tr[i].ls].siz + 1;
            i = tr[i].rs;
        }
    }
    return 0;
}

void add(int num) {
    tr[++cnt].key = num;
    tr[cnt].siz = 1;
    if (head == 0) {
        head = cnt;
    } else {
        int f = 0, i = head, son = 0;
        while (i != 0) {
            f = i;
            if (tr[i].key <= num) {
                son = 1;
                i = tr[i].rs;
            } else {
                son = 0;
                i = tr[i].ls;
            }
        }
        if (son == 1) {
            tr[f].rs = cnt;
        } else {
            tr[f].ls = cnt;
        }
        tr[cnt].fa = f;
        splay(cnt, 0);
    }
}

int getRank(int num) {
    int i = head, last = head;
    int ans = 0;
    while (i != 0) {
        last = i;
        if (tr[i].key >= num) {
            i = tr[i].ls;
        } else {
            ans += tr[tr[i].ls].siz + 1;
            i = tr[i].rs;
        }
    }
    splay(last, 0);
    return ans + 1;
}


int index(int x) {
    int i = find(x);
    splay(i, 0);
    return tr[i].key;
}

int pre(int num) {
    int i = head, last = head;
    int ans = INT_MIN;
    while (i != 0) {
        last = i;
        if (tr[i].key >= num) {
            i = tr[i].ls;
        } else {
            ans = max(ans, tr[i].key);
            i = tr[i].rs;
        }
    }
    splay(last, 0);
    return ans;
}

int post(int num) {
    int i = head, last = head;
    int ans = INT_MAX;
    while (i != 0) {
        last = i;
        if (tr[i].key <= num) {
            i = tr[i].rs;
        } else {
            ans = min(ans, tr[i].key);
            i = tr[i].ls;
        }
    }
    splay(last, 0);
    return ans;
}

void remove(int num) {
    int kth = getRank(num);
    if (kth != getRank(num + 1)) {
        int i = find(kth);
        splay(i, 0);
        if (tr[i].ls == 0) {
            head = tr[i].rs;
        } else if (tr[i].rs == 0) {
            head = tr[i].ls;
        } else {
            int j = find(kth + 1);
            splay(j, i);
            tr[j].ls = tr[i].ls;
            tr[tr[j].ls].fa = j;
            up(j);
            head = j;
        }
    }
    if (head != 0) {
        tr[head].fa = 0;
    }
}

void solve() {
    cin >> n;
    for (int i = 0, op, x; i < n; i++) {
    cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
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