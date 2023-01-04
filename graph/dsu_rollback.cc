// union find with rollback of specific operations
// useful for: https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_e

void nop(int a, int b) {}

template<void(*AddFun)(int, int) = nop, void(*SubFun)(int, int) = nop>
struct dsu_rollback {
	std::vector<int> parent;
	std::vector<int> ct;
	std::vector<pair<int, int>> op;

	dsu_rollback(int n) : parent(n), ct(n, 1) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int find(int i) {
		if (parent[i] == i) return i;
		return find(parent[i]);
	}

	bool unite(int i, int j) {
		int a = find(i);
		int b = find(j);
		op.emplace_back(-1, -1);
		if (a == b) return 0;
		if (ct[a] > ct[b]) std::swap(a, b);
		op.back() = std::make_pair(a, b);
		AddFun(a, b);
		ct[b] += ct[a];
		parent[a] = b;
		return 1;
	}

	// rollback the kth operation
	void rollback(int k) {
		assert(k < (int)op.size());
		auto [a, b] = op[k];
		if (a == -1) return;
		SubFun(a, b);
		ct[b] -= ct[a];
		parent[a] = a;
	}

	// rollback the last operation and remove it from the record
	void pop() {
		assert(!op.empty());
		rollback(op.size() - 1);
		op.pop_back();
	}
};
