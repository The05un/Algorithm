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
const int mod = 1e9 + 7;

int n;

struct AVL {
    int key;
    int height;
    int ls, rs;
    int key_count;
    int siz;
}tr[N];
int head = 0, cnt = 0;

void up(int i) {
    tr[i].siz = tr[tr[i].ls].siz + tr[tr[i].rs].siz + tr[i].key_count;
    tr[i].height = max(tr[tr[i].ls].height, tr[tr[i].rs].height) + 1;
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
    up(l);
    return l;
}

int maintain(int i) {
    int lh = tr[tr[i].ls].height;
    int rh = tr[tr[i].rs].height;
    if (lh - rh > 1) {
        if (tr[tr[tr[i].ls].ls].height >= tr[tr[tr[i].ls].rs].height) {
            i = rightRotate(i);
        } else {
            tr[i].ls = leftRotate(tr[i].ls);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (tr[tr[tr[i].rs].rs].height >= tr[tr[tr[i].rs].ls].height) {
            i = leftRotate(i);
        } else {
            tr[i].rs = rightRotate(tr[i].rs);
            i = leftRotate(i);
        }
    }
    return i;
}

int add(int i, int num) {
    if (i == 0) {
        tr[++cnt].key = num;
        tr[cnt].height = tr[cnt].key_count = tr[cnt].siz = 1;
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
    return maintain(i);
}

void add(int num) {
    head = add(head, num);
}

int getRank(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (tr[i].key >= num) {
        return getRank(tr[i].ls, num);
    } else {
        return tr[tr[i].ls].siz + tr[i].key_count + getRank(tr[i].rs, num);
    }
}

int getRank(int num) {
    return getRank(head, num) + 1;
}

int removeMostleft(int i, int mostleft) {
    if (i == mostleft) {
        return tr[i].rs;
    } else {
        tr[i].ls = removeMostleft(tr[i].ls, mostleft);
        up(i);
        return maintain(i);
    }
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
                int mostleft = tr[i].rs;
                while (tr[mostleft].ls != 0) {
                    mostleft = tr[mostleft].ls;
                }
                tr[i].rs = removeMostleft(tr[i].rs, mostleft);
                tr[mostleft].ls = tr[i].ls;
                tr[mostleft].rs = tr[i].rs;
                i = mostleft;
            }
        }
    }
    up(i);
    return maintain(i);
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (tr[tr[i].ls].siz >= x) {
        return index(tr[i].ls, x);
    } else if (tr[tr[i].ls].siz + tr[i].key_count < x) {
        return index(tr[i].rs, x - tr[tr[i].ls].siz - tr[i].key_count);
    }
    return tr[i].key;
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

void clear() {
    memset(tr, 0, (cnt + 1) * sizeof(AVL));
    cnt = 0;
    head = 0;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
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