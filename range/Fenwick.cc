/*
	1D Prefix sums and point updates.
	1-indexed.
	Time:
		- upd: O(log(N))
		- get: O(log(N))
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

	// adds val to the element at index idx
	void upd(int idx, T val) {
		for (int i = idx; i < len; i += i & -i) {
			data[i] += val;
		}
	}

	// returns the sum of elements in the range [1, idx]
	T get(int idx) {
		T res = 0;
		for (int i = idx; i > 0; i -= i & -i) {
			res += data[i];
		}
		return res;
	}

	// returns the sum of the elements in the range [left, right]
	T get(int left, int right) {
		return get(right) - get(left - 1);
	}
}; // Fenwick