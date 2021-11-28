// 1D Range Queries and Point Updates.
// 0-indexed.
// Time: 
// 	- build_Segtree: O(N)
// 	- upd: O(log(N))
// 	- get: O(log(N))
// Source: https://cp-algorithms.com/data_structures/segment_tree.html
struct segtree {
	struct node;
	std::vector<node> data;
	int len;

	segtree(int _len) : data(4 * _len), len(_len) {}

	segtree(std::vector<node>& input) : data(4 * input.size()), len(input.size()) {
		build_Segtree(1, 0, len - 1, input);
	}

	// builds the segtree using the nodes in the input array
	void build_Segtree(int i, int tl, int tr, vector<node>& input) {
		if (tl == tr) {
			data[i] = input[tl]; // the current node is a leaf
			return;
		}
		// this node is not a leaf, recurse on children
		int tm = (tl + tr) / 2;
		build_Segtree(i * 2, tl, tm, input);
		build_Segtree(i * 2 + 1, tm + 1, tr, input);
		// set the value of this node by combining the values of its children
		data[i] = combine(data[i * 2], data[i * 2 + 1]);
	}

	// sets the element at index x to v
	void upd(int i, int tl, int tr, int x, const node& v) {
		if (tl == x && tr == x) {
			data[i] = v; // we are at x
			return;
		}
		// we are not at x, recurse on the child that has x as a leaf
		int tm = (tl + tr) / 2;
		if (x <= tm) upd(i * 2, tl, tm, x, v);
		else upd(i * 2 + 1, tm + 1, tr, x, v);
		// update the current node
		data[i] = combine(data[i * 2], data[i * 2 + 1]);
	}

	// sets the element at index x to v
	void upd(int x, const node& v) {
		upd(1, 0, len - 1, x, v);
	}

	// queries the segment [l, r]
	node get(int i, int tl, int tr, int l, int r) {
		if (tr < l || tl > r) return node(); // we are out of range, return the default value
		if (tl >= l && tr <= r) return data[i]; // this node's entire segment is in the range 
		// we are partially in the range, recurse on children
		int tm = (tl + tr) / 2;
		return combine(get(i * 2, tl, tm, l, r), get(i * 2 + 1, tm + 1, tr, l, r));
	}

	// queries the segment [l, r]
	node get(int l, int r) {
		return get(1, 0, len - 1, l, r);
	}

// --------------------------------------
	// CHANGE
	struct node {
		long long v = 0;
	};
	node combine(const node& a, const node& b) {
		return {a.v + b.v};
	}
// --------------------------------------
}; //segtree 

using node = segtree::node;