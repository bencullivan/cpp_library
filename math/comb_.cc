constexpr int mod = 998244353

long long modpow(long long a, long long b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

using mint = modnum<1000000007>;
// using mint = modnum<998244353>;

vector<long long> facts, ifacts;

// all factorials up to and including n, mod m
void gen_facts(int n) {
	if (!facts.empty()) return;
	facts.resize(n + 1);
	facts[0] = 1;
	for (int i = 1; i <= n; i++) facts[i] = facts[i - 1] * i;
	ifacts.resize(n + 1);
	ifacts[n] = facts[n].inv();
	for (int i = n; i > 0; i--) ifacts[i - 1] = ifacts[i] * i;
}

// n permute k, mod m
mint perm(int n, int k) {
	//if (n >= (int)facts.size()) throw runtime_error("call gen_facts before calling perm");
	//assert(n >= k);
	return facts[n] * ifacts[n - k];
}

// n choose k, mod m
mint choose(int n, int k) {
	return perm(n, k) * ifacts[k];
}

// nth catalan number, mod m
mint catalan(int n) {
	return choose(2 * n, n) - choose(2 * n, n + 1);
}