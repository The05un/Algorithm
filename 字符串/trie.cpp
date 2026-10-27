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
const int mod = 1e9 + 7;

int n;

struct trie {
    int tree[26];
    int end;
    int pass;
}tr[N];
int cnt;

void build() {
    cnt = 1;
}

void insert(const string &s) {
    int cur = 1;
    tr[cur].pass++;
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int path = s[i] - 'a';
        if (tr[cur].tree[path] == 0) {
            tr[cur].tree[path] = ++cnt;
        }
        cur = tr[cur].tree[path];
        tr[cur].pass++;
    }
    tr[cur].end++;
}

int Find(const string &s) {
    int cur = 1;
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int path = s[i] - 'a';
        if (tr[cur].tree[path] == 0) {
            return 0;
        }
        cur = tr[cur].tree[path];
    }
    return tr[cur].end;
}

int findPre(const string &s) {
    int cur = 1;
    int sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int path = s[i] - 'a';
        if (tr[cur].tree[path] == 0) {
            return 0;
        }
        cur = tr[cur].tree[path];
    }
    return tr[cur].pass;
}

void deleTe(const string & s) {
    if (Find(s) > 0) {
        int cur = 1;
        tr[cur].pass--;
        int sz = s.size();
        for (int i = 0; i < sz; ++i) {
            int path = s[i] - 'a';
            if (--tr[tr[cur].tree[path]].pass == 0) {
                tr[cur].tree[path] = 0;
                return;
            }
            cur = tr[cur].tree[path];
        }
        tr[cur].end--;
    }
}

void clean() {
    for (int i = 1; i <= cnt; ++i) {
        memset(tr[i].tree, 0, sizeof(tr[i].tree));
        tr[i].end = 0;
        tr[i].pass = 0;
    }
}

void solve() {
    build();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int op; cin >> op;
        string s; cin >> s;
        if (op == 1) {
            insert(s);
        } else if (op == 2) {
            deleTe(s);
        } else if (op == 3) {
            if (Find(s)) cout << "YES\n";
            else cout << "NO\n";
        } else {
            cout << findPre(s) << "\n";
        }
    }
    clean();
} 


int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}