/*
	1D Range Max/Min Queries and Range Updates.
	0-indexed.
	Currently op == 1 for assignment and op == 2 for addition, however, this can be changed to support other operations.
	Time:
		- build_LazyM: O(N)
		- upd: O(log(N))
		- get: O(log(N))
	Sources:
		- https://cp-algorithms.com/data_structures/segment_tree.html
		- kostia244 (cf) https://codeforces.com/blog/entry/80182
*/
struct LazyM {
	struct Lazy;
	struct Node;
	vector<Node> data;
	int len;

	LazyM(int _len) : data(4 * _len), len(_len) {}

	LazyM(vector<Node>& input) : data(4 * input.size()), len(input.size()) {
		build_LazyM(1, 0, len - 1, input);
	}

	// builds the Segtree using the nodes in the input array
	void build_LazyM(int i, int tl, int tr, vector<Node>& input) {
		if (tl == tr) {
			// the current node is a leaf
			data[i] = input[tl];
			return;
		}
		// this node is not a leaf -> recurse on children
		int tm = (tl + tr) >> 1;
		build_LazyM(i << 1, tl, tm, input);
		build_LazyM(i << 1 | 1, tm + 1, tr, input);
		// set the value of this node by combining the values of its children
		data[i] = combine(data[i << 1], data[i << 1 | 1]);
	}

	// pushes updates to the children of node i
	void push(int i, int tl, int tr) {
		// handle the different operation types when updating the current node
		if (data[i].lazy.op == 1) {
			data[i].v = data[i].lazy.v;
		}
		else if (data[i].lazy.op == 2) {
			data[i] = push_combine(data[i], data[i].lazy);
		}
		if (tl != tr) {
			// this node is not a leaf -> push updates to children
			data[i << 1].lazy = lazy_combine(data[i << 1].lazy, data[i].lazy);
			data[i << 1 | 1].lazy = lazy_combine(data[i << 1 | 1].lazy, data[i].lazy);
		}
		// reset the lazy info of the current node
		data[i].lazy = Lazy();
	}

	// combines v with the elements in the range [l, r]
	void upd(int i, int tl, int tr, int l, int r, const Lazy& lazy) {
		push(i, tl, tr); // always push for the current node
		if (tl > r || tr < l) {
			return;
		} 
		if (tl >= l && tr <= r) {
			data[i].lazy = lazy_combine(data[i].lazy, lazy); // update the lazy info of this node
			push(i, tl, tr); // immediately push the new update
			return;
		}
		int tm = (tl + tr) >> 1;
		// we are partially in the range -> recurse on children
		upd(i << 1, tl, tm, l, r, lazy);
		upd(i << 1 | 1, tm + 1, tr, l, r, lazy);
		data[i] = combine(data[i << 1], data[i << 1 | 1]);
	}

	// combines v with the elements in the range [l, r]
	void upd(int l, int r, const Lazy& lazy) {
		upd(1, 0, len - 1, l, r, lazy);
	}

	// queries the range [l, r]
	Node get(int i, int tl, int tr, int l, int r) {
		push(i, tl, tr); // always push for the current node
		if (tl > r || tr < l) {
			return Node(); // we are out of the range -> return the default value
		} 
		if (tl >= l && tr <= r) {
			return data[i]; // this node's entire segment is in the range
		}
		// we are partially in the range -> recurse on children
		int tm = (tl + tr) >> 1;
		return combine(get(i << 1, tl, tm, l, r), get(i << 1 | 1, tm + 1, tr, l, r));
	}

	// queries the range [l, r]
	Node get(int l, int r) {
		return get(1, 0, len - 1, l, r);
	}

// --------------------------------------
	// CHANGE

	struct Lazy {
		int op = 0; // the lazy operation type (0 means no operation)
		long long v = -5e18;
	};
	Lazy lazy_combine(const Lazy& a, const Lazy& b) {
		// determines how the lazy info of two nodes is combined, assume b was updated after a
		if (b.op == 2) {
			return {a.op == 1 ? 1 : 2, a.v + b.v}; // if a is an assignment, leave it as an assigment
		}
		else if (b.op == 1) {
			return b; // since b is an assignment we overwrite the lazy info of a
		}
		else {
			return a; // since b has no operation, leave a unchanged
		}
	}

	struct Node {
		Lazy lazy;
		long long v = -5e18;
	};
	Node combine(const Node& a, const Node& b) {
		// the function with which two nodes are combined during queries
		return {Lazy(), max(a.v, b.v)};
	}
	Node push_combine(const Node& a, const Lazy& b) {
		// the function with which two nodes are combined during updates
		return {b, a.v + b.v};
	}
// --------------------------------------
}; // LazyM