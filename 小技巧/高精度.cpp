#include<bits/stdc++.h>
using namespace std;
struct BigInt {
    static const int BASE = 1e9;
    vector<int> a;
    int sign;
    
    BigInt() : sign(1) {}
    BigInt(long long v) { *this = v; }
    BigInt(const string& s) { read(s); }
    
    BigInt& operator=(long long v) {
        sign = 1;
        if (v < 0) sign = -1, v = -v;
        a.clear();
        for (; v > 0; v /= BASE) a.push_back(v % BASE);
        return *this;
    }
    
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= 9) {
            int x = 0;
            for (int j = max(pos, i - 8); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    
    void trim() {
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }
    
    bool isZero() const { return a.empty(); }
    
    BigInt operator-() const {
        BigInt res = *this;
        res.sign = -sign;
        return res;
    }
    
    BigInt abs() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }
    
    bool operator<(const BigInt& v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
        return false;
    }
    
    bool operator>(const BigInt& v) const { return v < *this; }
    bool operator<=(const BigInt& v) const { return !(v < *this); }
    bool operator>=(const BigInt& v) const { return !(*this < v); }
    bool operator==(const BigInt& v) const { return !(*this < v) && !(v < *this); }
    bool operator!=(const BigInt& v) const { return *this < v || v < *this; }
    
    BigInt& operator+=(const BigInt& v) {
        if (sign == v.sign) {
            for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
                if (i == (int)a.size()) a.push_back(0);
                a[i] += carry + (i < (int)v.a.size() ? v.a[i] : 0);
                carry = a[i] >= BASE;
                if (carry) a[i] -= BASE;
            }
        } else if (abs() >= v.abs()) {
            for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
                a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
                carry = a[i] < 0;
                if (carry) a[i] += BASE;
            }
            trim();
        } else {
            *this = v + *this;
        }
        return *this;
    }
    
    BigInt& operator-=(const BigInt& v) {
        return *this += -v;
    }
    
    BigInt& operator*=(const BigInt& v) {
        vector<int> res(a.size() + v.a.size());
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0, carry = 0; j < (int)v.a.size() || carry; ++j) {
                long long cur = res[i + j] + (long long)a[i] * (j < (int)v.a.size() ? v.a[j] : 0) + carry;
                carry = (int)(cur / BASE);
                res[i + j] = (int)(cur % BASE);
            }
        a = res;
        sign *= v.sign;
        trim();
        return *this;
    }
    
    BigInt& operator/=(const BigInt& v) {
        return *this = divmod(*this, v).first;
    }
    
    BigInt& operator%=(const BigInt& v) {
        return *this = divmod(*this, v).second;
    }
    
    friend BigInt operator+(BigInt a, const BigInt& b) { return a += b; }
    friend BigInt operator-(BigInt a, const BigInt& b) { return a -= b; }
    friend BigInt operator*(BigInt a, const BigInt& b) { return a *= b; }
    friend BigInt operator/(BigInt a, const BigInt& b) { return a /= b; }
    friend BigInt operator%(BigInt a, const BigInt& b) { return a %= b; }
    
    static pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        int norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q, r;
        q.a.resize(a.a.size());
        
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= BASE;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long)BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) r += b, --d;
            q.a[i] = d;
        }
        
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    
    BigInt operator/(int v) const {
        BigInt res = *this;
        int rem = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            long long cur = a[i] + rem * (long long)BASE;
            res.a[i] = (int)(cur / v);
            rem = (int)(cur % v);
        }
        res.sign = sign * (v > 0 ? 1 : -1);
        res.trim();
        return res;
    }
    
    int operator%(int v) const {
        int rem = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i)
            rem = (a[i] + rem * (long long)BASE) % v;
        return rem * sign;
    }

    void print() const {
        if (isZero()) {
            printf("0");
            return;
        }
        if (sign == -1) printf("-");
        printf("%d", a.empty() ? 0 : a.back());
        for (int i = (int)a.size() - 2; i >= 0; --i)
            printf("%09d", a[i]);
    }
};
BigInt gcd(BigInt a,BigInt b){return b>0?gcd(b,a%b):a;}
BigInt Lcm(BigInt a,BigInt b){return a*b/gcd(a,b);}
signed main(){
    string a,b;
    cin>>a>>b;
    BigInt num1(a);
    BigInt num2(b);
    BigInt ans1,ans2,ans3,ans4,ans5;
    ans1=num1+num2;
    ans2=num1-num2;
    ans3=num1*num2;
    ans4=num1/num2;
    ans5=num1%num2;
    ans3.print();
    cout<<'\n';
}