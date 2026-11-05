#include<bits/stdc++.h>
using namespace std;

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define Rep(i, a, b) for(int i=(a);i<=static_cast<int>(b);++i)
#define Dep(i, a, b) for(int i=(a);i>=static_cast<int>(b);--i)
#define rep(i, a, b) for(int i=(a);i<static_cast<int>(b);++i)
#define mem(x, v, sz) memset(x,v,(sz+1)*sizeof(int))
#define debug(x) cout << #x" = " << (x) << "\n"
#define pp(x, y) cout << "pp: " << (x) << " " << (y) << "\n"

#define int int

#define fi first
#define se second
#define pir pair<int, int>
#define i64 long long
#define u64 unsigned long long
#define u32 unsigned
#define i128 __int128
#define u128 unsigned __int128
#define f64 double
#define ld long double

const int N = 3e5 + 5;
const int M = 1000 + 5;
const int mod = 998244353;
const int INF = 1e9 + 7;
const int NINF = -1e9 - 7;
const f64 EPS = 1e-9;

int n, q;

struct left {
    int num;
    int ls, rs, up;
    int dist;
}tr[N];

int fa[N], sz[N];
int add[N];
int addAll;

multiset<int> ms;

void reMove(int h) {
    if (h != 0) {
        int hnum = tr[h].num + add[h];
        auto it = ms.find(hnum);
        ms.erase(it);
    }
}

void Add(int h) {
    if (h != 0) {
        int hnum = tr[h].num + add[h];
        ms.insert(hnum);
    }
}

void prepare() {
    tr[0].dist = -1;
    ms.clear();
    Rep(i, 1, n) {
        tr[i].dist = tr[i].ls = tr[i].rs = tr[i].up = 0;
        fa[i] = i;
        sz[i] = 1;
        add[i] = 0;
        Add(i);
    }
    addAll = 0;
}

int find(int i) {
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (tr[i].num < tr[j].num || (tr[i].num == tr[j].num && i > j)) {
        swap(i, j);
    }
    tr[i].rs = merge(tr[i].rs, j);
    tr[tr[i].rs].up = i;
    if (tr[tr[i].ls].dist < tr[tr[i].rs].dist) {
        swap(tr[i].ls, tr[i].rs);
    }
    tr[i].dist = tr[tr[i].rs].dist + 1;
    fa[tr[i].ls] = fa[tr[i].rs] = i;
    return i;
}

int remove(int i) {
    int h = find(i);
    fa[tr[i].ls] = tr[i].ls;
    fa[tr[i].rs] = tr[i].rs;
    int s = merge(tr[i].ls, tr[i].rs);
    int f = tr[i].up;
    fa[i] = s;
    tr[s].up = f;
    if (h != i) {
        fa[s] = h;
        if (tr[f].ls == i) {
            tr[f].ls = s;
        } else {
            tr[f].rs = s;
        }
        for (int d = tr[s].dist; tr[f].dist > d + 1; d++, f = tr[f].up) {
            if (tr[tr[f].ls].dist < tr[tr[i].rs].dist) {
                swap(tr[f].ls, tr[f].rs);
            }
        }
    }
    tr[i].up = tr[i].ls = tr[i].rs = tr[i].dist = 0;
    return fa[s];
}

void update(int i, int v) {
    int h = remove(i);
    tr[i].num -= v;
    fa[h] = fa[i] = merge(i, h);
}

void down(int i, int v) {
    if (i != 0) {
        add[i] = 0;
        tr[i].num += v;
        down(tr[i].ls, v);
        down(tr[i].rs, v);
    }
}

void u(int i, int j) {    //加一条边，连接第 i 个节点和第 j 个节点
    int l = find(i);
    int r = find(j);
    if (l == r) {
        return;
    }
    int lsz = sz[l];
    reMove(l);
    int rsz = sz[r];
    reMove(r);
    int addTag;
    if (lsz <= rsz) {
        down(l, add[l] - add[r]);
        addTag = add[r];
    } else {
        down(r, add[r] - add[l]);
        addTag = add[l];
    }
    int h = merge(l, r);
    sz[h] = lsz + rsz;
    add[h] = addTag;
    Add(h);
}

void a1(int i, int v) {    //将第 i 个节点的权值增加 v
    int h = find(i);
    reMove(h);
    int l = remove(i);
    if (l != 0) {
        sz[l] = sz[h] - 1;
        add[l] = add[h];
        Add(l);
    }
    tr[i].num += add[h] + v;
    fa[i] = i;
    sz[i] = 1;
    add[i] = 0;
    Add(i);
    u(i, l);
}

void a2(int i, int v) {   //将第 i 个节点所在的连通块的所有节点的权值都增加 v
    int h = find(i);
    reMove(h);
    add[h] += v;
    Add(h);
}

void a3(int v) {   //将所有节点的权值都增加 v
    addAll += v;
}

int f1(int i) {    //输出第 x 个节点当前的权值
    return tr[i].num + add[find(i)] + addAll;
}

int f2(int i) {  //   输出第 x 个节点所在的连通块中，权值最大的节点的权值
    int h = find(i);
    return tr[h].num + add[h] + addAll;
}

int f3() {    //输出所有节点中，权值最大的节点的权值
    return *ms.rbegin() + addAll;
}

void solve() {
    cin >> n;
    Rep(i, 1, n) {
        cin >> tr[i].num;
    }
    prepare();
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        op = " " + op;
        if (op[1] == 'U') {
            int x, y;
            cin >> x >> y;
            u(x, y);
        } else if (op[1] == 'A') {
            if (op[2] == '1') {
                int x, v;
                cin >> x >> v;
                a1(x, v);
            } else if (op[2] == '2') {
                int x, v;
                cin >> x >> v;
                a2(x, v);
            } else {
                int v;
                cin >> v;
                a3(v);
            }
        } else {
            if (op[2] == '1') {
                int x;
                cin >> x;
                cout << f1(x) << "\n";
            } else if (op[2] == '2') {
                int x;
                cin >> x;
                cout << f2(x) << "\n";
            } else {
                cout << f3() << "\n";
            }
        }
    }
}


signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}