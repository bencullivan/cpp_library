// Various functions for searching within strings.
// Sources:
// - https://cp-algorithms.com/string/prefix-function.html
// - https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
// - https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Manacher.h

// Computes for each index, i, the length of the longest substring that is 
// both a prefix and a suffix of s[0...i]
// Time: O(n)
template <typename T>
vector<int> lps_function(const T& s, int n) {
	vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		// finds the lps at position i
		// consider the example abadfacabadfab and suppose we are at the final position
		// the j value would be 6 because abadfa == abadfa, however we cannot extend it because c != b
		// since we know that we can extend, we can restrict our search to the first 6 characters of the string
		// this is because we know that they are the same as the last 6 characters of the string ending at index i - 1
		// thus, we move to pi[j - 1]
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) j++; // if we have found a match, increment
		pi[i] = j;
	}
	return pi;
}

// Counts the number of occurrences of each prefix of s
// Time: O(n)
template <typename T>
vector<int> prefix_count(const T& s, int n) {
	vector<int> pi = lps_function(s);
	vector<int> occs(n + 1);
	for (int i = 0; i < n; i++) occs[pi[i]]++;
	for (int i = n - 1; i >= 0; i--) occs[pi[i - 1]] += occs[i];
	for (int i = 0; i <= n; i++) occs[i]++;
	return occs;
}

// Reference:
// D. Gusfield,
// Algorithms on Strings, Trees, and Sequences: Computer Science and
// Computational Biology
template <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {
	int n = int(s.size());
	if (n == 0) return {};
	std::vector<int> z(n);
	z[0] = 0;
	for (int i = 1, j = 0; i < n; i++) {
		int& k = z[i];
		k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
		while (i + k < n && s[k] == s[i + k]) k++;
		if (j + z[j] < i + z[i]) j = i;
	}
	z[0] = n;
	return z;
}

std::vector<int> z_algorithm(const std::string& s) {
	int n = int(s.size());
	std::vector<int> s2(n);
	for (int i = 0; i < n; i++) {
		s2[i] = s[i];
	}
	return z_algorithm(s2);
}

/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N)
 * Status: Stress-tested
 */
// #pragma once

template <typename T>
array<vector<int>, 2> manacher(const T& s) {
	int n = sz(s);
	array<vector<int>,2> p = {vector<int>(n+1), vector<int>(n)};
	for (int z = 0; z < 2; z++) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}