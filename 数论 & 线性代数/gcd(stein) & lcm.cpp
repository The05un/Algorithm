#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int N = 2e5 + 5;

ll a, b;

// 证明辗转相除法就是证明如下关系：
// gcd(a, b) = gcd(b, a % b)
// 假设a % b = r，即需要证明的关系为：gcd(a, b) = gcd(b, r)
// 证明过程：
// 因为a % b = r，所以如下两个等式必然成立
// 1) a = b * q + r，q为0、1、2、3....中的一个整数
// 2) r = a − b * q，q为0、1、2、3....中的一个整数
// 假设u是a和b的公因子，则有: a = s * u, b = t * u
// 把a和b带入2)得到，r = s * u - t * u * q = (s - t * q) * u
// 这说明 : u如果是a和b的公因子，那么u也是r的因子
// 假设v是b和r的公因子，则有: b = x * v, r = y * v
// 把b和r带入1)得到，a = x * v * q + y * v = (x * q + y) * v
// 这说明 : v如果是b和r的公因子，那么v也是a的公因子
// 综上，a和b的每一个公因子 也是 b和r的一个公因子，反之亦然
// 所以，a和b的全体公因子集合 = b和r的全体公因子集合
// 即gcd(a, b) = gcd(b, r)
// 证明结束
ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll stein(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    int k = 0;
    while ((a & 1) == 0 && (b & 1) == 0) {
        a >>= 1;
        b >>= 1;
        ++k;
    }
    while ((a & 1) == 0) a >>= 1;
    while (b != 0) {
        while ((b & 1) == 0) b >>= 1;
        if (a > b) swap(a, b);
        b -= a;
    }
    return a << k;
}

ll lcm(ll a, ll b) {
	return a / stein(a, b) * b;
}


void solve() {
	cin >> a >> b;
	if (a == 0 || b == 0) {
		cout << 0 << "\n";
		return;
	}
	ll g = stein(a, b);
	ll l = a / g * b;
	cout << "gcd: " << g << "\n";
	cout << "lcm: " << l << "\n";
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1; //cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}