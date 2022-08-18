#define ARRAY_DEQUE_SAFE 0
template <typename T> struct array_deque {
    int cap = 0, count = 0, front_ptr, back_ptr, count;
    vector<T> data;
    array_deque() {}
    array_deque(int _cap) { resize(max(_cap, 10)); }

    void resize(int _cap) {
        cap = _cap;
        data.resize(_cap);
        front_ptr = 0;
        back_ptr = 1;
        count = 0;
    }

    void push_back(const T &x) {
#if ARRAY_DEQUE_SAFE
        assert(count < cap);
#endif
        if (count == 0)
            front_ptr = pre(front_ptr);
        data[back_ptr] = x;
        back_ptr = nex(back_ptr);
        count++;
    }

    void push_front(const T &x) {
#if ARRAY_DEQUE_SAFE
        assert(count < cap);
#endif
        if (count == 0)
            back_ptr = nex(back_ptr);
        data[front_ptr] = x;
        front_ptr = pre(front_ptr);
        count++;
    }

    void pop_back() {
#if ARRAY_DEQUE_SAFE
        assert(count > 0);
#endif
        back_ptr = pre(back_ptr);
        if (--count == 0)
            front_ptr = back_ptr;
    }

    void pop_front() {
#if ARRAY_DEQUE_SAFE
        assert(count > 0);
#endif
        front_ptr = pre(front_ptr);
        if (--count == 0)
            back_ptr = front_ptr;
    }

    T &operator[](int i) {
#if ARRAY_DEQUE_SAFE
        assert(0 <= i && i < count);
#endif
        return front_ptr + i + 1 >= cap ? data[front_ptr + i + 1 - cap]
                                        : data[front_ptr + i + 1];
    }

    T &back() {
#if ARRAY_DEQUE_SAFE
        assert(count > 0);
#endif
        return data[pre(back_ptr)];
    }

    T &front() {
#if ARRAY_DEQUE_SAFE
        assert(count > 0);
#endif
        return data[nex(front_ptr)];
    }

    inline int pre(int x) { return x == 0 ? cap - 1 : x - 1; }

    inline int nex(int x) { return x == cap - 1 ? 0 : x + 1; }

    inline int size() { return count; }
}; // struct array_deque