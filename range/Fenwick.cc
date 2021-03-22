/*
    1D Prefix sums and point updates in O(log(n)).
    1-indexed.
*/
template<typename T>
struct Fenwick {
    std::vector<T> data;
    int len;

    // constructs a tree with every element initialized to 0
    Fenwick(int _len) : data(_len+1), len(_len + 1) {}

    // constructs the tree having the specified initial list of elements
    Fenwick(std::vector<T>& input) : data(input.size() + 1), len((int) input.size() + 1) {
        for (int i = 1; i < len; i++) {
            upd(i, input[i - 1]);
        }
    }

    // updates the element at index idx
    void upd(int idx, T val) {
        for (int i = idx; i < len; i += i & -i) {
            data[i] += val;
        }
    }

    // returns the sum of the range [1, idx] inclusive
    T get(int idx) {
        T res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += data[i];
        }
        return res;
    }

    // returns the sum of the range [left, right] inclusive
    T get(int left, int right) {
        return get(right) - get(left-1);
    }
}; // Fenwick