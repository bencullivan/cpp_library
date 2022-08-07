// source: https://cp-algorithms.com/string/prefix-function.html
template<typename T> vector<int> prefix_function(const T& s) {
	int n = (int)s.size();
	vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}