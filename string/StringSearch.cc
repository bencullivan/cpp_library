// Provides various operations for searching within strings.
// Source: https://cp-algorithms.com/string/prefix-function.html (lps, kmp, occs, unique)
struct StringSearch {
	vector<int> pi;
	vector<int> zarray;
	vector<int> locs; // the locations of the target pattern from kmp or z
	vector<int> occs; // the number of occurrences of each prefix

	// Computes for each index, i, the length of the longest string that is 
	// both a prefix and a suffix of s[0...i]
	// Time: O(N)
	void lps(string& s) {
		pi.resize(s.size());
		pi[0] = 0;
		for (int i = 1; i < (int) s.size(); i++) {
			// finds the lps at position i
			// consider the example abadfacabadfab and suppose we are at the final position
			// the j value would be 6 because abadfa == abadfa, however we cannot extend it because c != b
			// since we know that we can extend, we can restrict our search to the first 6 characters of the string
			// this is because we know that they are the same as the last 6 characters of the string ending at index i - 1
			// thus, we move to pi[j - 1]
			int j = pi[i - 1];
			while (j > 0 && s[i] != s[j]) {
				j = pi[j - 1];
			}
			// if we have found a match, increment
			if (s[i] == s[j]) {
				j++;
			}
			pi[i] = j;
		}
	}

	// KMP algorithm to find all the locations of string t in string s
	// Time: O(N+M)
	void kmp(string& s, string& t, const string& separator) {
		// make sure that separator does not occur in either string
		string q = t + separator + s;
		lps(q);
		locs.clear();
		for (int i = 2 * t.size(); i < (int) q.size(); i++) {
			if (pi[i] == (int) t.size()) {
				locs.push_back(i - 2 * t.size());
			}
		}
	}

	// Counts the number of occurrences of each prefix of s
	// Time: O(N)
	void get_occs(string& s) {
		if (pi.size() != s.size()) {
			lps(s);
		}
		bool must_fill = !occs.empty();
		occs.resize(s.size() + 1);
		if (must_fill) {
			fill(occs.begin(), occs.end(), 0);
		}
		for (int i = 0; i < (int) s.size(); i++) {
			occs[pi[i]]++;
		}
		for (int i = s.size() - 1; i >= 0; i--) {
			occs[pi[i - 1]] += occs[i];
		}
		for (int i = 0; i <= (int) s.size(); i++) {
			occs[i]++;
		}
	}

	// Counts the number of unique substrings that appear in s
	// Time: O(N^2)
	long long count_unique(string& s) {
		long long ct = 0;
		string t;
		for (int i = 0; i < (int) s.size(); i++) {
			t = s[i] + t;
			lps(t);
			ct += i + 1 - *max_element(pi.begin(), pi.end());
		}
		return ct;
	}

	// Generates the array used in the z algorithm
	// zarray[i] is the length of the longest substring beginning from s[i] that is also a prefix of s
	void z(string& s) {
		int left = -1;
		int right = -1;
		zarray.resize(s.size());
		zarray[0] = 0;
		for (int i = 1; i < (int) s.size(); i++) {
			if (i > right) { // we are outside the current window
				if (s[i] != s[0]) { // there is no prefix starting at position i
					zarray[i] = 0;
					continue;
				}
				// there is a prefix starting at position i
				left = right = i;
				// expand the current window while it remains a prefix of s
				while (right < (int) s.size() - 1 && s[right + 1] == s[right + 1 - left]) {
					right++;
				}
				zarray[i] = right - left + 1;
			}
			else {
				// we know that we are in the current window, so the substrings s[i-left...] and s[i...] 
				// are equal for at least right-i+1 more characters
				if (zarray[i - left] < right - i + 1) { // we remain inside the current window
					zarray[i] = zarray[i - left];
				}
				else { // we must expand the current window while it remains a prefix of s
					left = i;
					while (right < (int) s.size() - 1 && s[right + 1] == s[right + 1 - left]) {
						right++;
					}
					zarray[i] = right - i + 1;
				}
			}
		}
	}

	// Z algorithm to find all occurrences of t in s
	// Time: O(N+M)
	void z_search(string& s, string& t, const string& separator) {
		// make sure that separator does not occur in either string
		string q = t + separator + s;
		z(q);
		locs.clear();
		for (int i = t.size() + 1; i < (int) (q.size() - t.size()) + 1; i++) {
			if (zarray[i] == (int) t.size()) {
				locs.push_back(i - t.size() - 1);
			}
		}
	}
}; // StringSearch