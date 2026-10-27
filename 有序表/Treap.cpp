
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using i128 = __int128;
using u128 = unsigned __int128;

using f64 = double;
using ld = long double;

const int N = 1e7 + 5;
const int mod = 1e9 + 7;

struct Treap {
    int key;
    int key_count;
    int ls, rs;
    int siz;
    f64 priority;
}tr[N];
int cnt = 0;
int head = 0;

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + tr[i].key_count;
}

int leftRotate(int i) {
    int r = tr[i].rs;
    tr[i].rs = tr[r].ls;
    tr[r].ls = i;
    up(i);
    up(r);
    return r;
}

int rightRotate(int i) {
    int l = tr[i].ls;
    tr[i].ls = tr[l].rs;
    tr[l].rs = i;
    up(i);
    up(l);;
    return l;
}

int add(int i, int num) {
    if (i == 0) {
        tr[++cnt].key = num;
        tr[cnt].key_count = tr[cnt].siz = 1;
        tr[cnt].priority = static_cast<double>(rand()) / RAND_MAX;
        return cnt;
    }
    if (tr[i].key == num) {
        tr[i].key_count++;
    } else if (tr[i].key > num) {
        tr[i].ls = add(tr[i].ls, num);
    } else {
        tr[i].rs = add(tr[i].rs, num);
    }
    up(i);
    if (tr[i].ls != 0 && tr[tr[i].ls].priority > tr[i].priority) {
        return rightRotate(i);
    }
    if (tr[i].rs != 0 && tr[tr[i].rs].priority > tr[i].priority) {
        return leftRotate(i);
    }
    return i;
}

void add(int num) {
    head = add(head, num);
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (tr[i].key >= num) {
        return small(tr[i].ls, num);
    } else {
        return tr[tr[i].ls].siz + tr[i].key_count + small(tr[i].rs, num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (tr[tr[i].ls].siz >= x) {
        return index(tr[i].ls, x);
    } else if (tr[tr[i].ls].siz + tr[i].key_count < x) {
        return index(tr[i].rs, x - tr[tr[i].ls].siz - tr[i].key_count);
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

int remove(int i, int num) {
    if (tr[i].key < num) {
        tr[i].rs = remove(tr[i].rs, num);
    } else if (tr[i].key > num) {
        tr[i].ls = remove(tr[i].ls, num);
    } else {
        if (tr[i].key_count > 1) {
            tr[i].key_count--;
        } else {
            if (tr[i].ls == 0 && tr[i].rs == 0) {
                return 0;
            } else if (tr[i].ls != 0 && tr[i].rs == 0) {
                i = tr[i].ls;
            } else if (tr[i].ls == 0 && tr[i].rs != 0) {
                i = tr[i].rs;
            } else {
                if (tr[tr[i].ls].priority >= tr[tr[i].rs].priority) {
                    i = rightRotate(i);
                    tr[i].rs = remove(tr[i].rs, num);
                } else {
                    i = leftRotate(i);
                    tr[i].ls = remove(tr[i].ls, num);
                }
            }
        }
    }
    up(i);
    return i;
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        head = remove(head, num);
    }
}

void clear() {
    memset(tr + 1, 0, cnt * sizeof(Treap));
    cnt = 0;
    head = 0;
}

int n;

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