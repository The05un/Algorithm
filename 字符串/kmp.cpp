#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 1e6 + 5;
const int M = 1e4 + 5;

int n, m;
int str[N], pattern[M];
int Next[M];

void getNext(int *p, int plen) {
    Next[0] = 0;
    Next[1] = 0;
    for (int i = 1; i < plen; ++i) {
        int j = Next[i];
        while (j && p[i] != p[j]) {
            j = Next[j];
        }
        if (p[i] == p[j]) Next[i + 1] = j + 1;
        else Next[i + 1] = 0;
    }
}
void kmp(int *s, int *p) {
    int slen = n, plen = m;
    int j = 0;
    for (int i = 0; i < slen; ++i) {
        while (j && s[i] != p[j]) j = Next[j];
        if (s[i] == p[j]) j++;
        if (j == plen) {
            cout << i + 2 - plen << "\n";  // 1-based
            return;
        }
    }
    cout << "-1\n";
}


void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> str[i];
    for (int i = 0; i < m; ++i) cin >> pattern[i];
    getNext(pattern, m);
    kmp(str, pattern);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}