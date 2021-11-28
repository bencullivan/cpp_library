struct xor_trie {
	std::vector<std::array<int, 2>> tr, ct;
	int lg;

	xor_trie() : xor_trie(30) {}
	xor_trie(int _lg) : tr(1, std::array<int, 2>{0, 0}), ct(1, std::array<int, 2>{0, 0}), lg(_lg-1) {}

	void insert(long long x) {
		int j = 0;
		for (int i = lg; i >= 0; i--) {
			int b = x>>i&1;
			if (tr[j][b] == 0) {
				tr[j][b] = tr.size();
				tr.push_back({0, 0});
				ct.push_back({0, 0});
			}
			ct[j][b]++;
			j = tr[j][b];
		}
	}

	void erase(long long x) {
		int j = 0;
		for (int i = lg; i >= 0; i--) {
			int b = x>>i&1;
			int nj = tr[j][b];
			if (--ct[j][b] == 0) {
				tr[j][b] = 0;
			}
			j = nj;
		}
	}

	// returns the max xor of x with any of the numbers in the trie
	long long get_max(long long x) {
		int j = 0;
		long long mx = 0;
		for (int i = lg; i >= 0; i--) {
			int b = x>>i&1;
			if (tr[j][b^1]) {
				mx |= 1LL<<i;
				j = tr[j][b^1];
			} else {
				j = tr[j][b];
			}
		}
		return mx;
	}

	// returns the number of y in the trie such that x^y < low
	long long count_less(long long x, long long low) {
		int j = 0;
		int c = 0;
		for (int i = lg; i >= 0 && (i == lg || j > 0); i--) {
			int b = (low>>i&1)^(x>>i&1);
			if (low>>i&1) c += ct[j][b^1];
			j = tr[j][b];
		}
		return c;
	}

	// returns the number of y in the trie such that x^y > high
	long long count_greater(long long x, long long high) {
		int j = 0;
		int c = 0;
		for (int i = lg; i >= 0 && (i == lg || j > 0); i--) {
			int b = (high>>i&1)^(x>>i&1);
			if ((high>>i&1) == 0) c += ct[j][b^1];
			j = tr[j][b];
		}
		return c;
	}
}; // struct xor_trie