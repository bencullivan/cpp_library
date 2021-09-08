// Fast Fourier Transform mod an arbitrary integer.
// Sources:
//  - http://neerc.ifmo.ru/trains/toulouse/2017/fft.pdf
//  - http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
//  - various fft implementations on codeforces

// double is significantly faster than long double
// fast init only performs O(log(n)) cos and sin evaluations
// only change if extra high precision is needed
using db = double;
using cplx = complex<db>;
bool use_fast_init = true;
constexpr int LG2 = 20;
constexpr int FFT_N = (1 << LG2); // the max length of a polynomial (1048576)
const db PI = acos(db(-1));
int rev[FFT_N];
cplx rts[FFT_N];

void fft_init(int n, int lg2) {
    for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (lg2 - 1));
    for (int i = 0; i < (n >> 1); i++) {
        db alpha = 2 * PI * i / n;
        rts[i + (n >> 1)] = cplx(cos(alpha), sin(alpha));
    }
    for (int i = (n >> 1) - 1; i > 0; i--) rts[i] = rts[i << 1];
}

void fft_fast_init(int n, int lg2) {
    for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (lg2 - 1));
    rts[1] = cplx(1, 0);
    for (int k = 1; k < lg2; k++) {
        db alpha = 2 * PI / (1 << (k + 1));
        cplx z(cos(alpha), sin(alpha));
        for (int i = (1 << (k - 1)); i < (1 << k); i++) {
            rts[i << 1] = rts[i];
            rts[i << 1 | 1] = rts[i] * z;
        }
    }
}

void fft(vector<cplx>& a, int n) {
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) for (int i = 0; i < n; i += (k << 1)) for (int j = 0; j < k; j++) {
        cplx z = rts[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
    }
}

void fft_inv(vector<cplx>& a, int n) {
    reverse(a.begin() + 1, a.end());
    fft(a, n);
    db ndb = n;
    for (int i = 0; i < n; i++) a[i] = a[i] / ndb;
}

template<typename fft_mint>
vector<fft_mint> multiply(const vector<fft_mint>& a, const vector<fft_mint>& b, bool use_FFT_N = false) {
    static constexpr db point5 = 0.5;
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
    vector<cplx> c(n), d(n);
    for (int i = 0; i < (int)a.size(); i++) c[i] = cplx(a[i].v & mask, a[i].v >> base);
    for (int i = 0; i < (int)b.size(); i++) d[i] = cplx(b[i].v & mask, b[i].v >> base);
    fft(c, n);
    fft(d, n);
    vector<cplx> e(n), f(n);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
        e[i] = cplx(point5 * (c[i].real() + c[j].real()), point5 * (c[i].imag() - c[j].imag())) * d[i];
        f[i] = cplx(point5 * (c[i].imag() + c[j].imag()), point5 * (c[j].real() - c[i].real())) * d[i];
    }
    fft_inv(e, n);
    fft_inv(f, n);
    vector<fft_mint> out(m);
    for (int i = 0; i < m; i++) {
        ll x = e[i].real() + point5, y = e[i].imag() + point5, z = f[i].real() + point5, w = f[i].imag() + point5;
        out[i] = fft_mint(x + (((y + z) % mod) << base) + ((w % mod) << (base << 1)));
    }
    return out;
}