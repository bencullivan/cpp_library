/*
    1D Prefix sums and point updates in O(log(n)).
    1-indexed.
*/
template<typename T>
struct Fenwick {
    vector<T> data;
    int len;

    Fenwick(int _len) : data(_len+1), len(_len + 1) {}

    Fenwick(vector<T>& input) : data(input.size() + 1), len((int) input.size() + 1) {
        for (int i = 1; i < len; i++) {
            upd(i, input[i - 1]);
        }
    }

    void upd(int idx, T val) {
        for (int i = idx; i < len; i += i & -i) {
            data[i] += val;
        }
    }

    // [1, idx]
    T get(int idx) {
        T res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += data[i];
        }
        return res;
    }

    // [left, right]
    T get(int left, int right) {
        return get(right) - get(left - 1);
    }
}; // Fenwick