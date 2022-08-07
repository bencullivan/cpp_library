// Lazy Segtree inspired by the implementation from the AtCoder Library (except this one is recursive lol)
// Range updates and queries in O(log(n))
template <typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
	vector<S> segs;
	vector<F> lazy;
	int len;
	int ceil_pow(int x) { return x == (1<<(31-__builtin_clz(x))) ? x : 1<<(31-__builtin_clz(x)+1); }
	lazy_segtree(int _len) : segs(ceil_pow(_len) * 2 + 1), lazy(ceil_pow(_len) * 2 + 1), len(_len) {}
	lazy_segtree(const vector<S>& input) : segs(ceil_pow(input.size()) * 2 + 1), lazy(ceil_pow(input.size()) * 2 + 1), len(input.size()) {
		build(1, 0, len - 1, input);
	}
	void build(int i, int tl, int tr, const vector<S>& input) {
		if (tl == tr) {
			segs[i] = input[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(i * 2, tl, tm, input);
		build(i * 2 + 1, tm + 1, tr, input);
		segs[i] = op(segs[i * 2], segs[i * 2 + 1]);
	}
	void push(int i, int tl, int tr) {
		segs[i] = mapping(lazy[i], segs[i]);
		if (tl != tr) {
			lazy[i * 2] = composition(lazy[i], lazy[i * 2]);
			lazy[i * 2 + 1] = composition(lazy[i], lazy[i * 2 + 1]);
		}
		lazy[i] = id();
	}
	void upd(int i, int tl, int tr, int l, int r, const F& x) {
		push(i, tl, tr);
		if (tl > r || tr < l) return;
		if (tl >= l && tr <= r) {
			lazy[i] = composition(x, lazy[i]);
			push(i, tl, tr);
			return;
		}
		int tm = (tl + tr) / 2;
		upd(i * 2, tl, tm, l, r, x);
		upd(i * 2 + 1, tm + 1, tr, l, r, x);
		segs[i] = op(segs[i * 2], segs[i * 2 + 1]);
	}
	void upd(int l, int r, const F& x) { // lazy the segment [l,r]
		upd(1, 0, len - 1, l, r, x);
	}
	S get(int i, int tl, int tr, int l, int r) {
		push(i, tl, tr);
		if (tl > r || tr < l) return e();
		if (tl >= l && tr <= r) return segs[i];
		int tm = (tl + tr) / 2;
		return op(get(i * 2, tl, tm, l, r), get(i * 2 + 1, tm + 1, tr, l, r));
	}
	S get(int l, int r) { // queries the segment [l,r]
		return get(1, 0, len - 1, l, r);
	}
}; //lazy_segtree 
struct S { // segment
};
struct F { // lazy update
};
S op(S l, S r) { // the combine operation for two segments
}
S mapping(F l, S r) { // the update operation for a segment
}
F composition(F l, F r) { // composition of two lazy updates (l is applied after r)
}
S e() { return S(); } // the identity segment
F id() { return F(); } // the identity update
#define lazy_segtree lazy_segtree<S, op, e, F, mapping, composition, id>
