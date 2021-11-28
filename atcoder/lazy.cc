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
S e() { // the identity segment
	return S();
}
F id() { // the identity update
	return F();
}
using lazy_segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;