/**
 * Source: ecnerwala cp-book https://github.com/ecnerwala/cp-book
 */
template<int _MOD>
struct _modnum {
	static constexpr int MOD = _MOD;
	int v;
	_modnum() : v(0) {}
	_modnum(ll _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const _modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, _modnum& n) { ll v_; in >> v_; n = _modnum(v_); return in; }
	friend bool operator == (const _modnum& a, const _modnum& b) { return a.v == b.v; }
	friend bool operator != (const _modnum& a, const _modnum& b) { return a.v != b.v; }
	friend bool operator < (const _modnum& a, const _modnum& b) { return a.v < b.v; }
	friend bool operator > (const _modnum& a, const _modnum& b) { return a.v > b.v; }
	friend bool operator <= (const _modnum& a, const _modnum& b) { return a.v <= b.v; }
	friend bool operator >= (const _modnum& a, const _modnum& b) { return a.v >= b.v; }
	static int _minv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - ll(_minv(m, a)) * ll(m) / a);
	}
	_modnum inv() const {
		_modnum res;
		res.v = _minv(v, MOD);
		return res;
	}
	friend _modnum inv(const _modnum& m) { return m.inv(); }
	_modnum neg() const {
		_modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	friend _modnum neg(const _modnum& m) { return m.neg(); }
	_modnum operator- () const {
		return neg();
	}
	_modnum operator+ () const {
		return _modnum(*this);
	}
	_modnum& operator ++ () {
		v++;
		if (v == MOD) v = 0;
		return *this;
	}
	_modnum& operator -- () {
		if (v == 0) v = MOD;
		v--;
		return *this;
	}
	_modnum& operator += (const _modnum& o) {
		v -= MOD-o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	_modnum& operator -= (const _modnum& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	_modnum& operator *= (const _modnum& o) {
		v = int((ll)v * (ll)o.v % MOD);
		return *this;
	}
	_modnum& operator /= (const _modnum& o) {
		return *this *= o.inv();
	}
	friend _modnum operator ++ (_modnum& a, int) { _modnum r = a; ++a; return r; }
	friend _modnum operator -- (_modnum& a, int) { _modnum r = a; --a; return r; }
	friend _modnum operator + (const _modnum& a, const _modnum& b) { return _modnum(a) += b; }
	friend _modnum operator - (const _modnum& a, const _modnum& b) { return _modnum(a) -= b; }
	friend _modnum operator * (const _modnum& a, const _modnum& b) { return _modnum(a) *= b; }
	friend _modnum operator / (const _modnum& a, const _modnum& b) { return _modnum(a) /= b; }
}; // _modnum 

using mint = _modnum<1000000007>;
// using mint = _modnum<998244353>;

vector<mint> facts, ifacts;

// all factorials up to and including n, mod m
void gen_facts(ll n) {
	if (!facts.empty()) return;
	facts.resize(n + 1);
	facts[0] = 1;
	for (int i = 1; i <= n; i++) facts[i] = facts[i - 1] * i;
	ifacts.resize(n + 1);
	ifacts[n] = facts[n].inv();
	for (int i = n; i > 0; i--) ifacts[i - 1] = ifacts[i] * i;
}

// n permute k, mod m
mint perm(ll n, ll k) {
	if (n >= (ll)facts.size()) throw runtime_error("call gen_facts before calling perm");
	assert(n >= k);
	return facts[n] * ifacts[n - k];
}

// n choose k, mod m
mint comb(ll n, ll k) {
	return perm(n, k) * ifacts[k];
}

// nth catalan number, mod m
mint catalan(ll n) {
	return comb(2 * n, n) - comb(2 * n, n + 1);
}