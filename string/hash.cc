using ull = unsigned long long;

// Rolling String Hashing
// Time:
// 	- Build: O(N)
// 	- Query: O(1)
// Source: https://codeforces.com/blog/entry/60445

// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
    mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
    int base = uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}

struct PolyHash {
    static const int mod = (int)1e9+123; // prime mod of polynomial hashing
    static vector<int> pow1;             // powers of base modulo mod
    static vector<ull> pow2;             // powers of base modulo 2^64
    static int base;                     // base (point of hashing)

    vector<int> pref1; // Hash on prefix modulo mod
    vector<ull> pref2; // Hash on prefix modulo 2^64

    PolyHash(string& s) : pref1(s.size()+1u, 0), pref2(s.size()+1u, 0) {
        assert(base < mod);
        int n = s.size();
        while ((int)pow1.size() <= n) {
            pow1.push_back((long long)pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) {
            assert(base > s[i]);
            pref1[i+1] = (pref1[i] + (long long)s[i] * pow1[i]) % mod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }

    // Polynomial hash of subsequence [pos, pos+len)
    // If mx_pow != 0, value automatically multiply on base in needed power. Finally base ^ mx_pow 
    pair<int, ull> get(int pos, int len, int mx_pow = 0) {
        int hash1 = pref1[pos+len] - pref1[pos];
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mx_pow != 0) {
            hash1 = (long long)hash1 * pow1[mx_pow-(pos+len-1)] % mod;
            hash2 *= pow2[mx_pow-(pos+len-1)];
        }
        return make_pair(hash1, hash2);
    }
}; // PolyHash

// Returns whether the substring of one is lexicographically smaller than the substring of two
// Method: finds the location of the first differing character between the two strings and then compares that character
//         if there are no differing characters it compares based on substring length
// Time: O(log(substr_len))
bool comp_hash(string& one, PolyHash& one_hash, int one_start, int one_substr_len, 
                string& two, PolyHash& two_hash, int two_start, int two_substr_len, int mx_pow) {
    int loc = -1; // the location at which the substrings differ
    int low = 1, high = min(one_substr_len, two_substr_len);
    while (low <= high) {
        int mid = (low + high) / 2;
        if (one_hash.get(one_start, mid, mx_pow) == two_hash.get(two_start, mid, mx_pow)) low = mid + 1;
        else loc = mid, high = mid - 1;
    }
    if (loc == -1) return one_substr_len < two_substr_len;
    return one[one_start + loc - 1] < two[two_start + loc - 1];
}

vector<int> PolyHash::pow1{1};
vector<ull> PolyHash::pow2{1};
int PolyHash::base((int)1e9+7);
//DO: 
//mx_pow = maximum length of the strings being hashed
//PolyHash::base = gen_base(256, PolyHash::mod);