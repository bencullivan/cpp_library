/**
* Extended Euclidean algorithm for finding the solution (x, y) to ax+by = gcd(a,b)
* Returns gcd(a,b)
* Time: O(log(min(a,b))
* Source: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
*/
ll _extended_euclidean(ll a, ll b, ll& x, ll& y) {
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
* Modular inverse of a, mod m
* If m is prime, this is equivalent to mpow(a,m-2)
* Only exists if a and m are coprime
* Time: O(log(min(a,m)))
*/
ll mod_inv(ll a, ll m, bool prime = true) {
	if (prime) return mpow(a, m - 2);
	ll x, y;
	_extended_euclidean(a, m, x, y);
	return (x % m + m) % m;
}