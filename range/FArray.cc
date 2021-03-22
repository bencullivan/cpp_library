/*
    Finds the index of the first occurence of a value greater-equal/less-equal to a target value.
    0-indexed.
    Time:
        - build_FArray: O(N)
        - update: O(log(N))
        - get_first: O(log(N))
*/
template<typename T> 
struct FArray {
    int len;
    vector<T> data;

    FArray(int _len) {
        len = compute_pow(_len);
        data.resize(len << 1, query_start);
    }

    FArray(vector<T>& input) {
        len = compute_pow(input.size());
        data.resize(len << 1, query_start);
        build_FArray(input);
    }

    void build_FArray(vector<T>& input) {
        for (int i = 0; i < (int) input.size(); i++) {
            data[i + len] = input[i];
        }
        for (int i = len - 1; i > 0; i--) {
            data[i] = prefer(data[i << 1], data[i << 1 | 1]);
        }
    }

    // assigns value to the element at index idx
    void upd(int idx, T value) {
        data[idx += len] = value;
        while ((idx >>= 1) > 0) {
            data[idx] = prefer(data[idx << 1], data[idx << 1 | 1]);
        }
    }

    // gets the index of the first element that is preferable to value and also 
    // the value of the element at that index
    pair<int, T> get(T value) {
        if (data[1] != prefer(data[1], value)) {
            return make_pair(-1, query_start);
        }
        int idx = 1;
        while (idx < len) {
            idx <<= 1;
            if (data[idx] != prefer(data[idx], value)) {
                idx |= 1;
            }
        }
        return make_pair(idx - len, data[idx]);
    }

    int compute_pow(int x) {
        int t = log2(x);
        return 1 << t < x ? 1 << (t + 1) : 1 << t;
    }

// --------------------------------------
    // CHANGE
    const T& prefer(const T& a, const T& b) {
        return max(a, b);
    }
    const T query_start = INT_MIN;
// --------------------------------------
}; //FArray 