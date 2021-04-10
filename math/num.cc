const int MOD = 1e9+7;

// a to the b, mod m
long long mpow(long long a, long long b, long long m) {
    long long r = 1;
    for (; b > 0; a = a * a % m, b >>= 1) if (b & 1) r = r * a % m;
    return r;
}

// modular inverse of a, mod m
long long minv(long long a, long long m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : m - minv(m, a) * m / a;
}

namespace kactl {
/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Tested for all a,p <= 10000
 */
long long sqrt(long long a, long long p) {
    a %= p; if (a < 0) a += p;
    if (a == 0) return 0;
    assert(mpow(a, (p-1)/2, p) == 1); // else no solution
    if (p % 4 == 3) return mpow(a, (p+1)/4, p);
    // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
    long long s = p - 1, n = 2;
    int r = 0, m;
    while (s % 2 == 0)
        ++r, s /= 2;
    /// find a non-square mod p
    while (mpow(n, (p - 1) / 2, p) != p - 1) ++n;
    long long x = mpow(a, (s + 1) / 2, p);
    long long b = mpow(a, s, p), g = mpow(n, s, p);
    for (;; r = m) {
        long long t = b;
        for (m = 0; m < r && t != 1; ++m)
            t = t * t % p;
        if (m == 0) return x;
        long long gs = mpow(g, 1LL << (r - m - 1), p);
        g = gs * gs % p;
        x = x * gs % p;
        b = b * g % p;
    }
}

/**
 * Author: Bjorn Martinsson
 * Date: 2020-06-03
 * License: CC0
 * Source: own work
 * Description: Returns the smallest $x > 0$ s.t. $a^x = b \pmod m$, or
 * $-1$ if no such $x$ exists. modLog(a,1,m) can be used to
 * calculate the order of $a$.
 * Time: $O(\sqrt m)$
 * Status: tested for all 0 <= a,x < 500 and 0 < m < 500.
 */
long long mlog(long long a, long long b, long long m) {
    long long n = (long long) sqrt(m) + 1, e = 1, f = 1, j = 1;
    unordered_map<long long, long long> A;
    while (j <= n && (e = f = e * a % m) != b % m)
        A[e * b % m] = j++;
    if (e == b % m) return j;
    if (__gcd(m, e) == __gcd(m, b)) 
        for (long long i = 2; i < n+2; i++)
            if (A.count(e = e * f % m))
                return n * i - A[e];
    return -1;
}
}; // namespace kactl
#ifndef KACTL
#define KACTL
using namespace kactl;
#endif

/*
    Source: ecnerwala cp-book https://github.com/ecnerwala/cp-book
*/
struct mint {
    int v;
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const mint& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, mint& n) { long long v_; in >> v_; n = mint(v_); return in; }
    friend bool operator == (const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator != (const mint& a, const mint& b) { return a.v != b.v; }
    mint inv() const {
        mint res;
        res.v = minv(v, MOD);
        return res;
    }
    friend mint inv(const mint& m) { return m.inv(); }
    mint neg() const {
        mint res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend mint neg(const mint& m) { return m.neg(); }
    mint operator- () const {
        return neg();
    }
    mint operator+ () const {
        return mint(*this);
    }
    mint& operator ++ () {
        v++;
        if (v == MOD) v = 0;
        return *this;
    }
    mint& operator -- () {
        if (v == 0) v = MOD;
        v--;
        return *this;
    }
    mint& operator += (const mint& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    mint& operator -= (const mint& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    mint& operator *= (const mint& o) {
        v = int((long long)v * (long long)o.v % MOD);
        return *this;
    }
    mint& operator /= (const mint& o) {
        return *this *= o.inv();
    }
    friend mint operator ++ (mint& a, int) { mint r = a; ++a; return r; }
    friend mint operator -- (mint& a, int) { mint r = a; --a; return r; }
    friend mint operator + (const mint& a, const mint& b) { return mint(a) += b; }
    friend mint operator - (const mint& a, const mint& b) { return mint(a) -= b; }
    friend mint operator * (const mint& a, const mint& b) { return mint(a) *= b; }
    friend mint operator / (const mint& a, const mint& b) { return mint(a) /= b; }
}; // mint

vector<mint> facts, ifacts;

// all factorials up to and including n, mod m
void gen_facts(long long n) {
    if (!facts.empty()) return;
    facts.resize(n + 1);
    facts[0] = 1;
    for (int i = 1; i <= n; i++) facts[i] = facts[i - 1] * i;
    ifacts.resize(n + 1);
    ifacts[n] = minv(facts[n].v, MOD);
    for (int i = n; i > 0; i--) ifacts[i - 1] = ifacts[i] * i;
}

// n permute k, mod m
mint perm(long long n, long long k) {
    if (n >= (long long)facts.size()) {
        cout << "call gen_facts before calling perm" << endl;
        assert(0);
    }
    assert(n >= k);
    return facts[n] * ifacts[n - k];
}

// n choose k, mod m
mint comb(long long n, long long k) {
    return perm(n, k) * ifacts[k];
}

// the divisors of a beginning from start
template<typename T> vector<T> get_divs(T a, int start) {
    vector<T> low, high;
    T i = start;
    for (; i * i < a; i++) if (a % i == 0) low.push_back(i), high.push_back(a / i);
    if (i * i == a) low.push_back(i);
    reverse(high.begin(), high.end());
    low.insert(low.end(), high.begin(), high.end());
    return low;
}