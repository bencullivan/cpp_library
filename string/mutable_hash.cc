// source: https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp

template <typename T> T mod_inv_in_range(T a, T m) {
	// assert(0 <= a && a < m);
	T x = a, y = m;
	T vx = 1, vy = 0;
	while (x) {
		T k = y / x;
		y %= x;
		vy -= k * vx;
		std::swap(x, y);
		std::swap(vx, vy);
	}
	assert(y == 1);
	return vy < 0 ? m + vy : vy;
}

template <typename T> T mod_inv(T a, T m) {
	a %= m;
	a = a < 0 ? a + m : a;
	return mod_inv_in_range(a, m);
}

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

private:
	using ll = long long;

	int v;

public:

	modnum() : v(0) {}
	modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }

	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

	modnum inv() const {
		modnum res;
		res.v = mod_inv_in_range(v, MOD);
		return res;
	}
	friend modnum inv(const modnum& m) { return m.inv(); }
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	friend modnum neg(const modnum& m) { return m.neg(); }

	modnum operator- () const {
		return neg();
	}
	modnum operator+ () const {
		return modnum(*this);
	}

	modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	modnum& operator += (const modnum& o) {
		v -= MOD-o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	modnum& operator -= (const modnum& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	modnum& operator *= (const modnum& o) {
		v = int(ll(v) * ll(o.v) % MOD);
		return *this;
	}
	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}

	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

template <typename U, typename V> struct pairnum {
	U u;
	V v;

	pairnum() : u(0), v(0) {}
	pairnum(long long val) : u(val), v(val) {}
	pairnum(const U& u_, const V& v_) : u(u_), v(v_) {}

	friend std::ostream& operator << (std::ostream& out, const pairnum& n) { return out << '(' << n.u << ',' << ' ' << n.v << ')'; }
	friend std::istream& operator >> (std::istream& in, pairnum& n) { long long val; in >> val; n = pairnum(val); return in; }

	friend bool operator == (const pairnum& a, const pairnum& b) { return a.u == b.u && a.v == b.v; }
	friend bool operator != (const pairnum& a, const pairnum& b) { return a.u != b.u || a.v != b.v; }

	pairnum inv() const {
		return pairnum(u.inv(), v.inv());
	}
	pairnum neg() const {
		return pairnum(u.neg(), v.neg());
	}
	pairnum operator- () const {
		return pairnum(-u, -v);
	}
	pairnum operator+ () const {
		return pairnum(+u, +v);
	}

	pairnum& operator ++ () {
		++u, ++v;
		return *this;
	}
	pairnum& operator -- () {
		--u, --v;
		return *this;
	}

	pairnum& operator += (const pairnum& o) {
		u += o.u;
		v += o.v;
		return *this;
	}
	pairnum& operator -= (const pairnum& o) {
		u -= o.u;
		v -= o.v;
		return *this;
	}
	pairnum& operator *= (const pairnum& o) {
		u *= o.u;
		v *= o.v;
		return *this;
	}
	pairnum& operator /= (const pairnum& o) {
		u /= o.u;
		v /= o.v;
		return *this;
	}

	friend pairnum operator ++ (pairnum& a, int) { pairnum r = a; ++a; return r; }
	friend pairnum operator -- (pairnum& a, int) { pairnum r = a; --a; return r; }
	friend pairnum operator + (const pairnum& a, const pairnum& b) { return pairnum(a) += b; }
	friend pairnum operator - (const pairnum& a, const pairnum& b) { return pairnum(a) -= b; }
	friend pairnum operator * (const pairnum& a, const pairnum& b) { return pairnum(a) *= b; }
	friend pairnum operator / (const pairnum& a, const pairnum& b) { return pairnum(a) /= b; }
};

using mint = modnum<1000000007>;
// using mint = modnum<998244353>;

template<typename T>
struct Fenwick {
	vector<T> data;
	int len;
	Fenwick(int _len) : data(_len+1), len(_len+1) {}
	void add(int idx, T val) { 
		for (int i = idx; i < len; i += i&-i) data[i] += val;
	}
	T get(int idx) { // [1, idx]
		T res = 0;
		for (int i = idx; i > 0; i -= i&-i) res += data[i];
		return res;
	}
	T get(int left, int right) { // [left, right]
		return get(right)-get(left-1);
	}
}; // struct Fenwick

// Rolling String Hashing
// Time:
// 	- Build: O(N*log(N))
// 	- Query: O(log(N))
// Source: https://codeforces.com/blog/entry/60445, https://ideone.com/8fDG3W

// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
	mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
	int base = uniform_int_distribution<int>(before+1, after)(mt_rand);
	return base % 2 == 0 ? base-1 : base;
}

using poly_hash_mint = Modnum<1000000123>;
using ull = unsigned long long;

struct MutablePolyHash {
	static const int mod = (int)1e9+123; // prime mod of polynomial hashing
	static vector<poly_hash_mint> pow1;  // powers of base modulo mod
	static vector<ull> pow2;             // powers of base modulo 2^64
	static int base;                     // base (point of hashing)

	Fenwick<poly_hash_mint> pref1;       // hash on prefix modulo 1e9+123
	Fenwick<ull> pref2;                  // hash on prefix modulo 2^64

	MutablePolyHash(string& s) : pref1(s.size()), pref2(s.size()) {
		assert(base < mod);
		int n = s.size();
		while ((int)pow1.size() <= n) {
			pow1.push_back(pow1.back() * base);
			pow2.push_back(pow2.back() * base);
		}
		for (int i = 0; i < n; ++i) {
			assert(base > s[i]);
			pref1.add(i + 1, pow1[i] * poly_hash_mint((ll)s[i]));
			pref2.add(i + 1, pow2[i] * s[i]);
		}
	}

	// changes the character at position i to newch
	void swap(int i, char oldch, char newch) {
		poly_hash_mint old1 = pow1[i] * poly_hash_mint((ll)oldch);
		poly_hash_mint new1 = pow1[i] * poly_hash_mint((ll)newch);
		old1 = mod - old1;
		pref1.add(i + 1, old1 + new1);
		ull old2 = pow2[i] * oldch;
		ull new2 = pow2[i] * newch;
		old2 = -old2;
		pref2.add(i + 1, old2 + new2);
	}

	// Polynomial hash of subsequence [pos, pos+len)
	// If mx_pow != 0, value automatically multiply on base in needed power. Finally base ^ mx_pow 
	pair<poly_hash_mint, ull> get(int pos, int len, int mx_pow = 0) {
		poly_hash_mint hash1 = pref1.get(pos+len) - pref1.get(pos);
		ull hash2 = pref2.get(pos+len) - pref2.get(pos);
		if (mx_pow != 0) {
			hash1 *= pow1[mx_pow-(pos+len-1)];
			hash2 *= pow2[mx_pow-(pos+len-1)];
		}
		return make_pair(hash1, hash2);
	}
}; // MutablePolyHash 

// Returns whether the substring of one is lexicographically smaller than the substring of two
// Method: finds the location of the first differing character between the two strings and then compares that character
//         if there are no differing characters it compares based on substring length
// Time: O(log(substr_len)*log(N))
bool comp_hash(string& one, MutablePolyHash& one_hash, int one_start, int one_substr_len, 
				string& two, MutablePolyHash& two_hash, int two_start, int two_substr_len, int mx_pow) {
	int loc = -1; // the location at which the substrings differ
	int low = 1, high = min(one_substr_len, two_substr_len);
	while (low <= high) {
		int mid = (low + high) / 2;
		if (one_hash.get(one_start, mid, mx_pow) == two_hash.get(two_start, mid, mx_pow)) {
			low = mid + 1;
		}
		else {
			loc = mid;
			high = mid - 1;
		}
	}
	if (loc == -1) return one_substr_len < two_substr_len;
	return one[one_start + loc - 1] < two[two_start + loc - 1];
}

vector<poly_hash_mint> MutablePolyHash::pow1{1};
vector<ull> MutablePolyHash::pow2{1};
int MutablePolyHash::base((int)1e9+7);
//DO: MutablePolyHash::base = gen_base(256, MutablePolyHash::mod);
//mx_pow = maximum length of the strings being hashed