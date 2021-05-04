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

/*
	1D Prefix sums and point updates.
	1-indexed.
	Time:
		- upd: O(log(N))
		- get: O(log(N))
*/
template<typename T>
struct Fenwick {
	vector<T> data;
	int len;

	Fenwick(int _len) : data(_len+1), len(_len + 1) {}

	Fenwick(vector<T>& input) : data(input.size() + 1), len((int) input.size() + 1) {
		for (int i = 1; i < len; i++) {
			upd(i, input[i - 1]);
		}
	}

	// adds val to the element at index idx
	void upd(int idx, T val) {
		for (int i = idx; i < len; i += i & -i) {
			data[i] += val;
		}
	}

	// returns the sum of elements in the range [1, idx]
	T get(int idx) {
		T res = 0;
		for (int i = idx; i > 0; i -= i & -i) {
			res += data[i];
		}
		return res;
	}

	// returns the sum of the elements in the range [left, right]
	T get(int left, int right) {
		return get(right) - get(left - 1);
	}
}; // Fenwick

/*
	Rolling String Hashing
	Time:
		- Build: O(N*log(N))
		- Query: O(log(N))
	Source: https://codeforces.com/blog/entry/60445
*/

// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
	auto seed = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
	mt19937 mt_rand(seed);
	int base = uniform_int_distribution<int>(before+1, after)(mt_rand);
	return base % 2 == 0 ? base-1 : base;
}

using poly_hash_mint = _modnum<1000000123>;

struct MutablePolyHash {
	static const int mod = (int)1e9+123;	// prime mod of polynomial hashing
	static vector<poly_hash_mint> pow1;		// powers of base modulo mod
	static vector<ull> pow2;				// powers of base modulo 2^64
	static int base;						// base (point of hashing)

	Fenwick<poly_hash_mint> pref1; 			// hash on prefix modulo 1e9+123
	Fenwick<ull> pref2;						// hash on prefix modulo 2^64

	MutablePolyHash(string& s) : pref1(s.size()), pref2(s.size()) {
		assert(base < mod);
		int n = s.size();
		while ((int)pow1.size() <= n) {
			pow1.push_back(pow1.back() * base);
			pow2.push_back(pow2.back() * base);
		}
		for (int i = 0; i < n; ++i) {
			assert(base > s[i]);
			pref1.upd(i + 1, pow1[i] * poly_hash_mint((ll)s[i]));
			pref2.upd(i + 1, pow2[i] * s[i]);
		}
	}

	// changes the character at position i to newch
	void swap(int i, char oldch, char newch) {
		poly_hash_mint old1 = pow1[i] * poly_hash_mint((ll)oldch);
		poly_hash_mint new1 = pow1[i] * poly_hash_mint((ll)newch);
		old1 = mod - old1;
		pref1.upd(i + 1, old1 + new1);
		ull old2 = pow2[i] * oldch;
		ull new2 = pow2[i] * newch;
		old2 = -old2;
		pref2.upd(i + 1, old2 + new2);
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

/*
	Returns whether the substring of one is lexicographically smaller than the substring of two
	Method: finds the location of the first differing character between the two strings and then compares that character
			if there are no differing characters it compares based on substring length
	Time: O(log(substr_len)*log(N))
*/
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