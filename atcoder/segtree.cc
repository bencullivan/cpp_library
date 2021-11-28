struct S { // segment
};
S op(S l, S r) { // update operation for two segments
}
S e() { // the identity segment
	return S();
}
using segtree = atcoder::segtree<S, op, e>;