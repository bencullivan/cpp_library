// https://github.com/ecnerwala/cp-book
template<int _MOD> struct Modnum {
	static constexpr int MOD = _MOD;
	int v;
	Modnum() : v(0) {}
	Modnum(ll _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend istream& operator >> (istream& in, Modnum& n) { ll v_; in >> v_; n = Modnum(v_); return in; }
	friend ostream& operator << (ostream& out, const Modnum& n) { return out << int(n); }
	friend bool operator == (const Modnum& a, const Modnum& b) { return a.v == b.v; }
	friend bool operator != (const Modnum& a, const Modnum& b) { return a.v != b.v; }
	friend bool operator < (const Modnum& a, const Modnum& b) { return a.v < b.v; }
	friend bool operator > (const Modnum& a, const Modnum& b) { return a.v > b.v; }
	friend bool operator <= (const Modnum& a, const Modnum& b) { return a.v <= b.v; }
	friend bool operator >= (const Modnum& a, const Modnum& b) { return a.v >= b.v; }
	static int _minv(int a, int m) { a %= m; assert(a); return a == 1 ? 1 : int(m - ll(_minv(m, a)) * ll(m) / a); }
	Modnum inv() const { Modnum res; res.v = _minv(v, MOD); return res; }
	friend Modnum inv(const Modnum& m) { return m.inv(); }
	Modnum neg() const { Modnum res; res.v = v ? MOD-v : 0; return res; }
	friend Modnum neg(const Modnum& m) { return m.neg(); }
	Modnum operator- () const { return neg(); }
	Modnum operator+ () const { return Modnum(*this); }
	Modnum& operator ++ () { v++; if (v == MOD) v = 0; return *this; }
	Modnum& operator -- () { if (v == 0) v = MOD; v--; return *this; }
	Modnum& operator += (const Modnum& o) { v -= MOD-o.v; v = (v < 0) ? v + MOD : v; return *this; }
	Modnum& operator -= (const Modnum& o) { v -= o.v; v = (v < 0) ? v + MOD : v; return *this; }
	Modnum& operator *= (const Modnum& o) { v = int((ll)v * (ll)o.v % MOD); return *this; }
	Modnum& operator /= (const Modnum& o) { return *this *= o.inv(); }
	friend Modnum operator ++ (Modnum& a, int) { Modnum r = a; ++a; return r; }
	friend Modnum operator -- (Modnum& a, int) { Modnum r = a; --a; return r; }
	friend Modnum operator + (const Modnum& a, const Modnum& b) { return Modnum(a) += b; }
	friend Modnum operator - (const Modnum& a, const Modnum& b) { return Modnum(a) -= b; }
	friend Modnum operator * (const Modnum& a, const Modnum& b) { return Modnum(a) *= b; }
	friend Modnum operator / (const Modnum& a, const Modnum& b) { return Modnum(a) /= b; }
}; // Modnum 

using mint = Modnum<1000000007>;
// using mint = Modnum<998244353>;