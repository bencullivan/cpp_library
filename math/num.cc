/**
 * Extended Euclidean algorithm for finding the solution (x, y) to ax+by = gcd(a,b)
 * Returns gcd(a,b)
 * Time: O(log(min(a,b))
 * Source: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 */
ll ext_euc(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1;
    ll q, t;
    while (b > 0) {
        q = a / b;
        t = x - q * x1;
        x = x1;
        x1 = t;
        t = y - q * y1;
        y = y1;
        y1 = t;
        t = a - q * b;
        a = b;
        b = t;
    }
    return a;
}

/**
 * Solves the linear diophantine equation ax+by = c
 * Also can be used to solve the linear congruence relation 
 * ax % m = b % m, rewritten as ax+my = b
 * Returns whether a solution exists
 * Time: O(log(min(abs(a),abs(b)))
 * Source: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
 */
bool lin_dio(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    g = ext_euc(abs(a), abs(b), x, y);
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

/**
 * a to the b mod m
 * Time: O(log(b))
 */
ll mpow(ll a, ll b, ll m) {
    ll r = 1;
    for (; b > 0; a = a * a % m, b >>= 1) if (b & 1) r = r * a % m;
    return r;
}

/**
 * Modular inverse of a, mod m
 * If m is prime, this is equivalent to mpow(a,m-2)
 * Only exists if a and m are coprime
 * Time: O(log(min(a,m)))
 */
ll minv(ll a, ll m) {
    ll x, y;
    ext_euc(a, m, x, y);
    return x;
}

/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Tested for all a,p <= 10000
 */
ll msqrt(ll a, ll p) {
	a %= p; if (a < 0) a += p;
	if (a == 0) return 0;
	if (mpow(a, (p-1)/2, p) != 1) return (ll)-1e18; // no solution
	if (p % 4 == 3) return mpow(a, (p+1)/4, p);
	// a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
	ll s = p - 1, n = 2;
	int r = 0, m;
	while (s % 2 == 0)
		++r, s /= 2;
	/// find a non-square mod p
	while (mpow(n, (p - 1) / 2, p) != p - 1) ++n;
	ll x = mpow(a, (s + 1) / 2, p);
	ll b = mpow(a, s, p), g = mpow(n, s, p);
	for (;; r = m) {
		ll t = b;
		for (m = 0; m < r && t != 1; ++m)
			t = t * t % p;
		if (m == 0) return x;
		ll gs = mpow(g, 1LL << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
	}
    return 0;
}

/**
 * Euler's totient function
 * Calculates the number of integers in the range [1,a] that are coprime to a.
 * Properties:
 *      - If a is prime and b > 0, phi(a^b) = a^b - a^(b-1)
 *      - If a and b are coprime, phi(a*b) = phi(a)*phi(b)
 *      - If a and m are coprime, a^phi(m) % m = 1
 * Time: O(sqrt(N))
 * Source: https://cp-algorithms.com/algebra/phi-function.html
 */
ll phi(ll a) {
    ll r = a;
    for (ll i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            while (a % i == 0) a /= i;
            r -= r / i;
        }
    }
    if (a > 1) r -= r / a;
    return r;
}

/**
 * Calculates phi(i) for all i in the range [1,n]
 * Time: O(n*log(log(n)))
 * Source: https://cp-algorithms.com/algebra/phi-function.html 
 */
vector<ll> all_phi(ll n) {
    vector<ll> ph(n + 1);
    for (ll i = 0; i <= n; i++) ph[i] = i;
    for (ll i = 2; i <= n; i++) {
        if (ph[i] == i) {
            for (ll j = i; j <= n; j += i) {
                ph[j] -= ph[j] / i;
            }
        }
    }
    return ph;
}

/**
 * Chinese Remainder Theorem
 * Finds the smallest x such that for all i, x % md[i] = rem[i]
 * Time: O(N * log(max(md)))
 */
//#define ll __int128
ll crt(vector<ll>& rem, vector<ll>& md) {
    ll prod = 1;
    for (ll &a:mx) prod *= a;
    ll x = 0;
    for (int i = 0; i < (int)md.size(); i++) {
        ll cur = prod / md[i];
        x += rem[i] * cur * minv(cur, md[i]);
        x %= prod;
    }
    return x;
}
//#undef ll

/**
 * Gets all divisors of a beginning from start
 * Start is usually 1 or 2
 * Time: O(sqrt(a))
 */
vector<ll> get_divs(ll a, ll start) {
    vector<ll> low, high;
    ll i = start;
    for (; i * i < a; i++) if (a % i == 0) low.push_back(i), high.push_back(a / i);
    if (i * i == a) low.push_back(i);
    reverse(high.begin(), high.end());
    low.insert(low.end(), high.begin(), high.end());
    return low;
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
 *
 * Details: This algorithm uses the baby-step giant-step method to
 * find (i,j) such that a^(n * i) = b * a^j (mod m), where n > sqrt(m)
 * and 0 < i, j <= n. If a and m are coprime then a^j has a modular
 * inverse, which means that a^(i * n - j) = b (mod m$).
 *
 * However this particular implementation of baby-step giant-step works even
 * without assuming a and m are coprime, using the following idea:
 *
 * Assume p^x is a prime divisor of m. Then we have 3 cases
 *	 1. b is divisible by p^x
 *	 2. b is divisible only by some p^y, 0<y<x
 *	 3. b is not divisible by p
 * The important thing to note is that in case 2, modLog(a,b,m) (if
 * it exists) cannot be > sqrt(m), (technically it cannot be >= log2(m)).
 * So once all exponenents of a that are <= sqrt(m) has been checked, you
 * cannot have case 2. Case 2 is the only tricky case.
 *
 * So the modification allowing for non-coprime input invloves checking all
 * exponents of a that are <= n, and then handling the non-tricky cases by
 * a simple gcd(a^n,m) == gcd(b,m) check.
 */
ll dlog(ll a, ll b, ll m) {
	ll n = (ll) sqrt(m) + 1, e = 1, f = 1, j = 1;
	unordered_map<ll, ll> A;
	while (j <= n && (e = f = e * a % m) != b % m)
		A[e * b % m] = j++;
	if (e == b % m) return j;
	if (__gcd(m, e) == __gcd(m, b)) 
		for(ll i = 2; i < n+2; i++) if (A.count(e = e * f % m))
			return n * i - A[e];
	return -1;
}

/**
 * Primitive root
 * Finds a primitive root, a, modulo m such that 
 * for all integers b that are coprime to a, there exists an x such that a^x % m = b % m
 * A primitive root exists iff:
 *      - m is in {1,2,4}
 *      - m is a power of an odd prime number: m = (p^k)
 *      - m is 2 times a power of an odd prime number: m = 2*(p^k)
 * If primitive roots mod m exist, the number of primitive roots mod m is phi(phi(m))
 * Time: O(m * log(phi(m)) * log(m))  (assumes that phi(m) has log(phi(m)) divisors)
 * Source: https://cp-algorithms.com/algebra/primitive-root.html
 */
ll proot(ll m) {
    ll ph = phi(m);
    ll n = ph;
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    for (ll ans = 2; ans <= m; ans++) {
        bool good = 1;
        for (int i = 0; i < (int)factors.size(); i++) {
            good &= (mpow(ans, ph / factors[i], m) != 1);
        }
        if (good) return ans;
    }
    return -1;
}

/**
 * Discrete root
 * Finds one or all x such that x^a % m = b % m
 * m must be prime
 * Time: O(m * log(phi(m)) * log(m))  (assumes that phi(m) has log(phi(m)) divisors)
 * Source: https://cp-algorithms.com/algebra/discrete-root.html
 */
vector<ll> droot(ll a, ll b, ll m, bool find_all) {
    ll g = proot(m);
    assert(g != -1);
    ll ga = mpow(g, a, m);
    ll y = dlog(ga, b, m);
    if (!find_all) return {mpow(g, y, m)};
    // since m is prime, we know phi(m) == m - 1
    ll delta = (m - 1) / __gcd(a, m - 1);
    vector<ll> ans;
    for (ll i = y % delta; i < m - 1; i += delta) {
        ans.push_back(mpow(g, i, m));
    }
    return ans; // (not in sorted order)
}