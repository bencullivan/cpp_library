// https://github.com/ecnerwala/cp-book
template<int _MOD> 
struct Modnum {
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

// using mint = Modnum<1000000007>;
// using mint = Modnum<998244353>;

// Fast Fourier Transform mod an arbitrary integer.
// Sources:
//  - http://neerc.ifmo.ru/trains/toulouse/2017/fft.pdf
//  - http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
//  - various fft implementations on codeforces

// double is significantly faster than long double
// fast init only performs O(log(n)) cos and sin evaluations
// only change if extra high precision is needed
using db = double;
bool use_fast_init = true;
constexpr int LG2 = 20;
constexpr int FFT_N = (1 << LG2); // the max length of a polynomial

struct Complex {
	db r, i;
	Complex() : r(0), i(0) {}
	Complex(db _r, db _i) : r(_r), i(_i) {}
	friend Complex operator + (const Complex& a, const Complex& b) { return Complex(a.r + b.r, a.i + b.i); }
	friend Complex operator - (const Complex& a, const Complex& b) { return Complex(a.r - b.r, a.i - b.i); }
	friend Complex operator * (const Complex& a, const Complex& b) { return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	friend Complex operator / (const Complex& a, const ll& b) { return Complex(a.r / b, a.i / b); }
}; // Complex

const db PI = acos(db(-1));
int rev[FFT_N];
Complex rts[FFT_N];

void fft_init(int n, int lg2) {
	for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (lg2 - 1));
	for (int i = 0; i < (n >> 1); i++) {
		db alpha = 2 * PI * i / n;
		rts[i + (n >> 1)] = Complex(cos(alpha), sin(alpha));
	}
	for (int i = (n >> 1) - 1; i > 0; i--) rts[i] = rts[i << 1];
}

void fft_fast_init(int n, int lg2) {
	for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (lg2 - 1));
	rts[1] = Complex(1, 0);
	for (int k = 1; k < lg2; k++) {
		db alpha = 2 * PI / (1 << (k + 1));
		Complex z(cos(alpha), sin(alpha));
		for (int i = (1 << (k - 1)); i < (1 << k); i++) {
			rts[i << 1] = rts[i];
			rts[i << 1 | 1] = rts[i] * z;
		}
	}
}

void fft(vector<Complex>& a, int n) {
	for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k <<= 1) for (int i = 0; i < n; i += (k << 1)) for (int j = 0; j < k; j++) {
		Complex z = rts[j + k] * a[i + j + k];
		a[i + j + k] = a[i + j] - z;
		a[i + j] = a[i + j] + z;
	}
}

void fft_inv(vector<Complex>& a, int n) {
	reverse(a.begin() + 1, a.end());
	fft(a, n);
	for (int i = 0; i < n; i++) a[i] = a[i] / n;
}

template<typename fft_mint>
vector<fft_mint> multiply(const vector<fft_mint>& a, const vector<fft_mint>& b, bool use_FFT_N = false) {
	static constexpr db pf = 0.5;
	constexpr int mod = fft_mint::MOD;
	constexpr int base = 15;
	constexpr int mask = (1 << base) - 1;
	int m = a.size() + b.size() - 1;
	int n = 1, lg2 = 0;
	if (use_FFT_N) n = FFT_N, lg2 = LG2;
	else {
		while (n < m) n <<= 1, lg2++;
		if (use_fast_init) fft_fast_init(n, lg2);
		else fft_init(n, lg2);
	}
	vector<Complex> c(n), d(n);
	for (int i = 0; i < (int)a.size(); i++) c[i] = Complex(a[i].v & mask, a[i].v >> base);
	for (int i = 0; i < (int)b.size(); i++) d[i] = Complex(b[i].v & mask, b[i].v >> base);
	fft(c, n);
	fft(d, n);
	vector<Complex> e(n), f(n);
	for (int i = 0; i < n; i++) {
		int j = (n - i) & (n - 1);
		e[i] = Complex(pf * (c[i].r + c[j].r), pf * (c[i].i - c[j].i)) * d[i];
		f[i] = Complex(pf * (c[i].i + c[j].i), pf * (c[j].r - c[i].r)) * d[i];
	}
	fft_inv(e, n);
	fft_inv(f, n);
	vector<fft_mint> out(m);
	for (int i = 0; i < m; i++) {
		ll x = e[i].r + pf, y = e[i].i + pf, z = f[i].r + pf, w = f[i].i + pf;
		out[i] = fft_mint(x + (((y + z) % mod) << base) + ((w % mod) << (base << 1)));
	}
	return out;
}