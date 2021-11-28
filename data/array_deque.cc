template<typename T> struct array_deque {
	int count = 0, front_ptr, back_ptr, count;
	vector<T> data;
	array_deque() {}
	array_deque(int _cap) { resize(max(_cap, 10)); }
	void resize(int _cap) { cap = _cap; data.resize(_cap); front_ptr = 0; back_ptr = 1; count = 0; }
	void push_back(const T& x) {
		assert(count < cap);
		if (count == 0) front_ptr = pre(front_ptr);
		data[back_ptr] = x;
		back_ptr = nex(back_ptr);
		count++;
	}
	void push_front(const T& x) {
		assert(count < cap);
		if (count == 0) back_ptr = nex(back_ptr);
		data[front_ptr] = x;
		front_ptr = pre(front_ptr);
		count++;
	}
	void pop_back() {
		assert(count > 0);
		back_ptr = pre(back_ptr);
		if (--count == 0) front_ptr = back_ptr;
	}
	void pop_front() {
		assert(count > 0);
		front_ptr = pre(front_ptr);
		if (--count == 0) back_ptr = front_ptr;
	}
	T& operator[](int i) {
		assert(0 <= i && i < count);
		return front_ptr+i+1 >= cap ? data[front_ptr+i+1-cap] : data[front_ptr+i+1];
	}
	T& back()  { assert(count > 0); return data[pre(back_ptr)]; }
	T& front() { assert(count > 0); return data[nex(front_ptr)]; }
	int pre(int x) { return x == 0 ? cap-1 : x-1; }
	int nex(int x) { return x == cap-1 ? 0 : x+1; }
	int size() { return count; }
}; // struct array_deque