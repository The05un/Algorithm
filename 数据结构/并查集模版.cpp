#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 1010;

bool flag = 0;
int n, m;
int f[N];
int sz[N];
stack<int> st;
int hasht[N];

void build() {
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        sz[i] = 1;
    }
}
int find(int x) {
    while (x != f[x]) {
        st.push(x);
        x = f[x];
    }
    while (!st.empty()) {
        int t = st.top(); st.pop();
        f[t] = x;
    }
    return x;
}
void merge_set(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        if (sz[fx] >= sz[fy]) {
            sz[fx] += sz[fy];
            f[fy] = fx;
        } else {
            sz[fy] += sz[fx];
            f[fx] = fy;
        }
    }
}


void solve() {
    memset(hasht, 0, sizeof(hasht));
    cin >> n;
    if (n == 0) {
        flag = 1;
        return;
    }
    cin >> m;
    build();
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        merge_set(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        int tmp = find(i);
        hasht[tmp]++;
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (hasht[i]) cnt++;
    }
    cout << cnt - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (!flag) {
        solve();
    }
    return 0;
}