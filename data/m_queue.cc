// source:
// https://cp-algorithms.com/data_structures/stack_queue_modification.html
template <typename T, typename Comparator = std::less<T>> struct m_stack {
    Comparator comp;
    std::vector<T> data, mdata;
    void push(const T &v) {
        data.push_back(v);
        mdata.push_back(mdata.empty() || comp(v, mdata.back()) ? v
                                                               : mdata.back());
    }
    void pop() { data.pop_back(), mdata.pop_back(); }
    T top() { return data.back(); }
    T mm() { return mdata.back(); }
    size_t size() { return data.size(); }
    bool empty() { return data.empty(); }
}; // m_stack
template <typename T, typename Comparator = std::less<T>> struct m_queue {
    Comparator comp;
    m_stack<T, Comparator> one, two;
    void swap_stack() {
        while (!one.empty()) {
            two.push(one.top());
            one.pop();
        }
    }
    void push(const T &v) {
        if (two.empty())
            swap_stack();
        one.push(v);
    }
    void pop() {
        if (two.empty())
            swap_stack();
        two.pop();
    }
    T front() {
        if (two.empty())
            swap_stack();
        assert(!two.empty());
        return two.top();
    }
    T mm() {
        if (two.empty())
            swap_stack();
        assert(!two.empty());
        if (one.empty())
            return two.mm();
        return comp(one.mm(), two.mm()) ? one.mm() : two.mm();
    }
}; // m_queue