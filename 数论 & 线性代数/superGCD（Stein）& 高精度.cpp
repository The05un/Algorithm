#include<bits/stdc++.h>
using namespace std;

const int Base = 10000;
const int Capacity = 5000;

class BigInt{
private:
    int m_data[Capacity];
    int m_size;
    void removeLeadingZeros();
public:
    BigInt();
    BigInt(const BigInt& bi);
    BigInt(char s[]);
    BigInt(int k);
    BigInt& operator= (const BigInt& bi);
    void print(char end);
    int compare(const BigInt& bi) const;
    bool isZero() const;
    BigInt operator+ (const BigInt& bi) const;
    BigInt operator- (const BigInt& bi) const;
    BigInt operator* (const BigInt& bi) const;
    BigInt operator/ (const BigInt& bi) const;
    BigInt operator% (const BigInt& bi) const;
    bool isEven() const;
    BigInt operator/(int k) const;
    BigInt operator*(int k) const;
};

void BigInt::removeLeadingZeros() {
    while (m_size > 0 && m_data[m_size - 1] == 0) {
        m_size--;
    }
}

BigInt::BigInt() : m_size(0) {
    memset(m_data, 0, sizeof(m_data));
}
BigInt::BigInt(const BigInt& bi) : m_size(bi.m_size) {
    memcpy(m_data, bi.m_data, sizeof(bi.m_data));
}
BigInt::BigInt(char s[]) {
    int b = 1;
    m_size = 0;
    m_data[m_size] = 0;
    for (int i = strlen(s) - 1; i >= 0; --i) {
        m_data[m_size] += (s[i] - '0') * b;
        b *= 10;
        if (b >= Base) {
            b = 1;
            m_size++;
            m_data[m_size] = 0;
        }
    }
    if (m_data[m_size] > 0) m_size++;
    removeLeadingZeros();
}
BigInt::BigInt(int k) {
    int tmp = k;
    m_size = 0;
    while(tmp > 0) {
        m_data[m_size] = tmp % Base;
        tmp /= Base;
        m_size++;
    }
}
BigInt& BigInt::operator= (const BigInt& bi) {
    m_size = bi.m_size;
    memcpy(m_data, bi.m_data, sizeof(m_data));
    return *this;
}
void BigInt::print(char end) {
    cout << (m_size == 0 ? 0 : m_data[m_size - 1]);
    for (int i = m_size - 2; i >= 0; --i) {
        for (int j = Base/ 10; j > 0; j /= 10) {
            cout << (m_data[i] / j) % 10;
        }
    }
    cout << end;
}
int BigInt::compare(const BigInt& bi) const {
    if (bi.m_size != m_size) {
        return (m_size > bi.m_size ? 1 : -1);
    }
    for (int i = m_size - 1; i >= 0; --i) {
        if (m_data[i] != bi.m_data[i]) {
            return (m_data[i] > bi.m_data[i] ? 1 : -1);
        }
    }
    return 0;
}// a.compare(b)   a < b => -1   a = b => 0   a > b => 1
bool BigInt::isZero() const {
    return m_size == 0;
}
BigInt BigInt::operator+ (const BigInt& bi) const {
    BigInt ret;
    int i, carry = 0;
    for (i = 0; i < m_size || i < bi.m_size || carry > 0; ++i) {
        if (i < m_size) carry += m_data[i];
        if (i < bi.m_size) carry += bi.m_data[i];
        ret.m_data[i] = carry % Base;
        carry /= Base;
    }
    ret.m_size = i;
    return ret;
}
BigInt BigInt::operator- (const BigInt& bi) const {
    BigInt ret;
    int carry = 0;
    ret.m_size = m_size;
    for (int i = 0; i < ret.m_size; ++i) {
        ret.m_data[i] = m_data[i] - carry;
        if (i < bi.m_size) {
            ret.m_data[i] -= bi.m_data[i];
        }
        if (ret.m_data[i] < 0) {
            carry = 1;
            ret.m_data[i] += Base;
        } else {
            carry = 0;
        }
    }
    ret.removeLeadingZeros();
    return ret;
}
BigInt BigInt::operator* (const BigInt& bi) const {
    BigInt ret;
    ret.m_size = m_size + bi.m_size;
    for (int i = 0; i < ret.m_size; ++i) {
        ret.m_data[i] = 0;
    }
    for (int i = 0; i < m_size; ++i) {
        int carry = 0;
        for (int j = 0; j < bi.m_size; ++j) {
            ret.m_data[i + j] += m_data[i] * bi.m_data[j] + carry;
            if (ret.m_data[i + j] >= Base) {
                carry = ret.m_data[i + j] / Base;
                ret.m_data[i + j] %= Base;
            } else {
                carry = 0;
            }
        }
        if (carry > 0) ret.m_data[i + bi.m_size] += carry;
    }
    ret.removeLeadingZeros();
    return ret;
}
BigInt BigInt::operator/ (const BigInt& bi) const {
    BigInt ret, carry = 0;
    int left, right, mid;
    for (int i = m_size - 1; i >= 0; --i) {
        carry = carry * Base + m_data[i];
        left = -1;
        right = Base;
        while (left + 1 < right) {
            mid = (left + right) >> 1;
            if ((bi * mid).compare(carry) <= 0) {
                left = mid;
            } else {
                right = mid;
            }
        }
        ret.m_data[i] = left;
        carry = carry - (bi * left);
    }
    ret.m_size = m_size;
    ret.removeLeadingZeros();
    return ret;
}
BigInt BigInt::operator% (const BigInt& bi) const {
    BigInt carry = 0;
    int left, right, mid;
    for (int i = m_size - 1; i >= 0; --i) {
        carry = carry * Base + m_data[i];
        left = -1;
        right = Base;
        while (left + 1 < right) {
            mid = (left + right) >> 1;
            if ((bi * mid).compare(carry) <= 0) {
                left = mid;
            } else {
                right = mid;
            }
        }
        carry = carry - (bi * left);
    }
    return carry;
}
bool BigInt::isEven() const {
    if (m_size == 0) return true;
    return m_data[0] % 2 == 0;
}
BigInt BigInt::operator/(int k) const {
    BigInt ret;
    long long carry = 0;
    for (int i = m_size - 1; i >= 0; --i) {
        long long cur = carry * Base + m_data[i];
        ret.m_data[i] = cur / k;
        carry = cur % k;
    }
    ret.m_size = m_size;
    ret.removeLeadingZeros();
    return ret;
}
BigInt BigInt::operator*(int k) const {
    BigInt ret;
    long long carry = 0;
    int i = 0;
    for (; i < m_size; ++i) {
        long long cur = 1LL * m_data[i] * k + carry;
        ret.m_data[i] = cur % Base;
        carry = cur / Base;
    }
    while (carry > 0) {
        ret.m_data[i++] = carry % Base;
        carry /= Base;
    }
    ret.m_size = i;
    return ret;
}

BigInt gcd(BigInt a, BigInt b) {
    if (a.isZero()) return b;
    if (b.isZero()) return a;
    int cnt = 0;
    while (a.isEven() && b.isEven()) {
        a = a / 2;
        b = b / 2;
        cnt++;
    }
    while (!a.isZero()) {
        while (a.isEven()) {
            a = a / 2;
        }
        while (b.isEven()) {
            b = b / 2;
        }
        if (a.compare(b) >= 0) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    while (cnt--) {
        b = b * 2;
    }
    return b;
}

int main() {
    char s1[10005], s2[10005];
    cin >> s1 >> s2;
    BigInt a(s1);
    BigInt b(s2);
    gcd(a, b).print('\n');
    return 0;
}