/**
* a to the b mod m
* Time: O(log(b))
*/
ll mod_pow(ll a, ll b, ll m) {
	ll r = 1;
	while (b > 0) {
		if (b & 1) r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;
}