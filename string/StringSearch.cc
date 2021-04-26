/*
    Provides various operations for searching within strings.
    Source: https://cp-algorithms.com/string/prefix-function.html (lps, kmp, occs, unique)
*/
struct StringSearch {
    vector<int> pi; // pi[i] is the length of the longest prefix of s that is also a suffix of the substring ending at i
    vector<int> zarray; // zarray[i] is the length of the longest substring beginning from s[i] that is also a prefix of s
    vector<int> locs; // the locations of the target pattern from kmp or z
    vector<int> occs; // the number of occurrences of each prefix

    /*
        Computes for each index, i, the length of the longest string that is 
        both a prefix and a suffix of s[0...i]
        Time: O(N)
    */
    void lps(string& s) {
        pi.resize(s.size());
        pi[0] = 0;
        for (int i = 1; i < (int) s.size(); i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = pi[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            pi[i] = j;
        }
    }

    /*
        KMP algorithm to find all the locations of string t in string s
        Time: O(N+M)
    */
    void kmp(string& s, string& t, const string& separator) {
        string q = t + separator + s;
        lps(q);
        locs.clear();
        for (int i = 2 * t.size(); i < (int) q.size(); i++) {
            if (pi[i] == (int) t.size()) {
                locs.push_back(i - 2 * t.size());
            }
        }
    }

    /*
        Counts the number of occurrences of each prefix of s
        Time: O(N)
    */
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

    /*
        Counts the number of unique substrings that appear in s.
        Time: O(N^2)
    */
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

    /*
        Generates the array used in the z algorithm.
    */
    void z(string& s) {
        int left = -1;
        int right = -1;
        zarray.resize(s.size());
        zarray[0] = 0;
        for (int i = 1; i < (int) s.size(); i++) {
            if (i > right) {
                if (s[i] != s[0]) {
                    zarray[i] = 0;
                    continue;
                }
                left = right = i;
                while (right < (int) s.size() - 1 && s[right + 1] == s[right + 1 - left]) {
                    right++;
                }
                zarray[i] = right - left + 1;
            } else {
                if (zarray[i - left] < right - i + 1) {
                    zarray[i] = zarray[i - left];
                } else {
                    left = i;
                    while (right < (int) s.size() - 1 && s[right + 1] == s[right + 1 - left]) {
                        right++;
                    }
                    zarray[i] = right - i + 1;
                }
            }
        }
    }

    /*
        Z algorithm to find all occurrences of t in s
        Time: O(N+M)
    */
    void z_search(string& s, string& t, const string& separator) {
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