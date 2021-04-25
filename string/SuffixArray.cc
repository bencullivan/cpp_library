/**
 * Suffix Array
 * Time: O(N*log(N))
 * Source: https://cp-algorithms.com/string/suffix-array.html
*/
struct SuffixArray {
    const int alphabet = 256;
    int len;
    vector<int> p; // the starting indices of substrings (in sorted order based on substrings)
    vector<int> c; // the equivalence class of the substring beginning at index i
    vector<int> ct; // the number of occurrences of each character

    void sort_cyclic_shifts(const string& s) {
        for (int i = 0; i < len; i++) {
            ct[s[i]]++;
        }
        for (int i = 1; i < alphabet; i++) {
            ct[i] += ct[i - 1];
        }
        for (int i = 0; i < len; i++) {
            p[--ct[s[i]]] = i;
        }
        int classes = 1;
        for (int i = 1; i < len; i++) {
            if (s[p[i]] != s[p[i - 1]]) {
                classes++;
            }
            c[p[i]] = classes - 1;
        }
        vector<int> newp(len);
        vector<int> newc(len);
        for (int k = 0; 1 << k < len; k++) {
            for (int i = 0; i < len; i++) {
                newp[i] = p[i] - (1 << k);
                if (newp[i] < 0) {
                    newp[i] += len;
                }
            }
            fill(ct.begin(), ct.begin() + classes, 0);
            for (int i = 0; i < len; i++) {
                ct[c[newp[i]]]++;
            }
            for (int i = 0; i < classes; i++) {
                ct[i] += ct[i - 1];
            }
            for (int i = len - 1; i >= 0; i--) {
                p[--ct[c[newp[i]]]] = newp[i];
            }
            newc[p[0]] = 0;
            classes = 1;
            for (int i = 0; i < len; i++) {
                if (c[p[i]] != c[p[i - 1]] || c[(p[i] + (1 << k)) % len] != c[(p[i - 1] + (1 << k)) % len]) {
                    classes++;
                }
                newc[p[i]] = classes - 1;
            }
            c.swap(newc);
        }
    }

    void build(const string& s, const string& separator) {
        string q = s + separator;
        len = q.size();
        p = vector<int>(len);
        c = vector<int>(len);
        ct = vector<int>(max(len, alphabet));
        sort_cyclic_shifts(q);
        // remember that if separator is "", skip the 0th entry of p
    }
}; // SuffixArray