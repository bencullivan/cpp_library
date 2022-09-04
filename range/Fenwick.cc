template <typename T> struct Fenwick {
    Fenwick(int len) : data(len + 1), len(len + 1) {}
    void add(int idx, T val) {
        for (int i = idx; i < len; i += (i & -i)) data[i] += val;
    }
    T get(int idx) { // [1, idx]
        T res = 0;
        for (int i = idx; i > 0; i -= (i & -i)) res += data[i];
        return res;
    }
    T get(int left, int right) { // [left, right]
        return get(right) - get(left - 1);
    }
    std::vector<T> data;
    int len;
};