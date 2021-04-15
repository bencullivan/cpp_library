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