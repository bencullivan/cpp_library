template <typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct SparseSegtree {
#define node SparseSegtree<S, op, e, F, mapping, composition, id>
    node *lc, *rc;
    int l, r, m;
    S val;
    F lazy;
    node(int L, int R)
        : lc(nullptr), rc(nullptr), l(L), r(R), m((L + R) / 2), val(e()),
          lazy(id()) {
        assert(L <= R);
    }
    ~node() {
        if (lc)
            delete lc;
        if (rc)
            delete rc;
    }
    void push() {
        val = mapping(lazy, val);
        if (lc)
            lc->lazy = composition(lazy, lc->lazy);
        if (rc)
            rc->lazy = composition(lazy, rc->lazy);
        lazy = id();
    }
    S get(int L, int R) {
        push();
        if (R < l || r < L)
            return e();
        if (L <= l && r <= R)
            return val;
        return op(lc ? lc->get(L, R) : e(), rc ? rc->get(L, R) : e());
    }
    void upd(int L, int R, const F &x) {
        push();
        if (R < l || r < L)
            return;
        if (L <= l && r <= R) {
            lazy = composition(x, lazy);
            push();
        } else {
            if (!lc)
                lc = new node(l, m);
            if (!rc)
                rc = new node(m + 1, r);
            lc->upd(L, R, x);
            rc->upd(L, R, x);
            val = op(lc->val, rc->val);
        }
    }
#undef node
};
struct S { // segment
};
struct F { // lazy update
};
S op(S l, S r) { // the combine operation for two segments
}
S mapping(F l, S r) { // the update operation for a segment
}
F composition(F l,
              F r) { // composition of two lazy updates (l is applied after r)
}
S e() { // the identity segment
    return S();
}
F id() { // the identity update
    return F();
}
using lazy = SparseSegtree<S, op, e, F, mapping, composition, id>;