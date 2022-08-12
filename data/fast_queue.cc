template<typename T>
struct fast_queue {
    int l = 0;
    std::vector<T> data;
    fast_queue() {}
    fast_queue(int _n) { data.reserve(_n); }
    void push(T x) { data.push_back(x); }
    void pop() { l++; }
    T& front() { return data[l]; }
    int size() { return static_cast<int>(data.size())-l; }
};