template<typename T, bool use_min = true> struct RMQ { // Build in O(N*log(N)). Query in O(1). Sources: kactl, Neal Wu.
	vector<T> vals;
	vector<vector<int>> table;
	int select_index(int a, int b) { return (use_min ? vals[a] < vals[b] : vals[a] > vals[b]) ? a : b; }
	RMQ() {}
	RMQ(const vector<T>& vl) { build(vl); }
	void build(const vector<T>& vl) {
		vals = vl;
		table.resize(1, vector<int>(vals.size()));
		for (int i = 0; i < (int)vals.size(); i++) table[0][i] = i;
		for (int pw = 1, k = 1; pw * 2 <= (int)vals.size(); pw *= 2, k++) {
			table.emplace_back((int)vl.size() - pw * 2 + 1);
			for (int j = 0; j < (int)table[k].size(); j++) 
				table[k][j] = select_index(table[k - 1][j], table[k - 1][j + pw]);
		}
	}
	T get_index(int a, int b) { // gets the minimum of the range [a, b)
		int dep = 31 - __builtin_clz(b - a);
		return select_index(table[dep][a], table[dep][b - (1 << dep)]);
	}
	T get_val(int a, int b) { return vals[get_index(a, b)]; }
}; // RMQ