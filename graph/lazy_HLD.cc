// https://github.com/atcoder/ac-library
#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1
namespace atcoder {
namespace internal {
// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned)(n)) x++;
    return x;
}
// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned n) {
    return __builtin_ctz(n);
}
}  // namespace internal
}  // namespace atcoder
#endif  // ATCODER_INTERNAL_BITOP_HPP
#ifndef ATCODER_LAZYSEGTREE_HPP
#define ATCODER_LAZYSEGTREE_HPP 1
namespace atcoder {
template <class S,
        S (*op)(S, S),
        S (*e)(),
        class F,
        S (*mapping)(F, S),
        F (*composition)(F, F),
        F (*id)()>
struct lazy_segtree {
public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    S prod(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (l & 1) push(l >> i);
            if (r & 1) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) { // [l, r)
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (l & 1) push(l >> i);
            if (r & 1) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (l & 1) update(l >> i);
            if (r & 1) update((r - 1) >> i);
        }
    }
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
}  // namespace atcoder
#endif  // ATCODER_LAZYSEGTREE_HPP
// struct S { // segment
// };
// struct F { // lazy update
// };
// S op(S l, S r) { // the combine operation for two segments
// }
// S mapping(F l, S r) { // the update operation for a segment
// }
// F composition(F l, F r) { // composition of two lazy updates (l is applied after r)
// }
// S e() { return S(); } // the identity segment
// F id() { return F(); } // the identity update
// using Lazy = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
// Build in O(N*log(N)). Query in O(1). Sources: kactl, Neal Wu.
template<typename T>
struct HLD_RMQ {
    vector<T> vals;
    vector<vector<int>> table;
    int select_index(int a, int b) { return vals[a] < vals[b] ? a : b; }
    HLD_RMQ() {}
    HLD_RMQ(const vector<T>& _vals) { build(_vals); }
    void build(const vector<T>& _vals) {
        vals = _vals;
        table.resize(1, vector<int>(vals.size()));
        for (int i = 0; i < (int)vals.size(); i++) table[0][i] = i;
        for (int pw = 1, k = 1; pw * 2 <= (int)vals.size(); pw *= 2, k++) {
            table.emplace_back((int)vals.size() - pw * 2 + 1);
            for (int j = 0; j < (int)table[k].size(); j++) 
                table[k][j] = select_index(table[k - 1][j], table[k - 1][j + pw]);
        }
    }
    T get_index(int a, int b) { // gets the minimum of the range [a, b)
        int dep = 31 - __builtin_clz(b - a);
        return select_index(table[dep][a], table[dep][b - (1 << dep)]);
    }
    T get_val(int a, int b) { return vals[get_index(a, b)]; }
}; //HLD_RMQ 
// Build in O(N*log(N)). Query in O(1).
struct HLD_LCA {
    vector<int> first_euler, euler;
    vector<int> depth;
    HLD_RMQ<int> rmq;
    HLD_LCA() {}
    HLD_LCA(int root, const vector<vector<int>>& tr) : first_euler(tr.size()) {
        euler.reserve(2 * tr.size()), depth.reserve(2 * tr.size());
        dfs(root, -1, 0, tr);
        rmq.build(depth);
    }
    void dfs(int u, int v, int d, const vector<vector<int>>& tr) {
        first_euler[u] = euler.size();
        euler.push_back(u), depth.push_back(d);
        for (int x:tr[u]) if (x != v) {
            dfs(x, u, d + 1, tr);
            euler.push_back(u), depth.push_back(d);
        }
    }
    int get_lca(int u, int v) { 
        return euler[rmq.get_index(min(first_euler[u], first_euler[v]), max(first_euler[u], first_euler[v]) + 1)]; 
    }
}; //HLD_LCA 
template<bool VALS_EDGES, typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct HeavyLightDecomposition {
    vector<int> par, heavy, head, pos;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> st;
    HLD_LCA lca;
    int root;
    HeavyLightDecomposition(int _root, const vector<vector<int>>& tr) :
        par(tr.size(), _root), heavy(tr.size(), -1), head(tr.size()), 
        pos(tr.size()), st(tr.size()), lca(_root, tr), root(_root) {
            assign_heavy(root, tr);
            int idx = 0;
            decompose(root, root, idx, tr);
            assert(idx == (int)tr.size());
        }
    HeavyLightDecomposition(int _root, const vector<vector<int>>& tr, const vector<S>& vals) :
        par(tr.size(), _root), heavy(tr.size(), -1), head(tr.size()),
        pos(tr.size()), lca(_root, tr), root(_root) {
            assign_heavy(root, tr);
            int idx = 0;
            decompose(root, root, idx, tr);
            assert(idx == (int)tr.size());
            vector<S> ordered_vals(vals.size());
            for (int i = 0; i < (int)vals.size(); i++) ordered_vals[pos[i]] = vals[i];
            st = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>(ordered_vals);
        }
    int assign_heavy(int u, const vector<vector<int>>& tr) {
        int size = 1, max_x_size = 0;
        for (int x:tr[u]) if (x != par[u]) {
            par[x] = u;
            int x_size = assign_heavy(x, tr);
            if (x_size > max_x_size) max_x_size = x_size, heavy[u] = x;
            size += x_size;
        }
        return size;
    }
    void decompose(int u, int h, int& idx, const vector<vector<int>>& tr) {
        head[u] = h, pos[u] = idx++;
        if (heavy[u] != -1) decompose(heavy[u], h, idx, tr);
        for (int x:tr[u]) if (x != par[u] && x != heavy[u]) decompose(x, x, idx, tr);
    }
    void upd_vertical(int u, int ancestor, const F& x, bool dont_update_ancestor) {
        for (; head[u] != head[ancestor]; u = par[head[u]]) st.apply(pos[head[u]], pos[u] + 1, x);
        st.apply(pos[ancestor] + dont_update_ancestor, pos[u] + 1, x);
    }
    void upd(int u, int v, const F& x) {
        if (u == v) {
            st.apply(pos[u], pos[u] + 1, x);
            return;
        }
        int top = lca.get_lca(u, v);
        if (u == top) upd_vertical(v, top, x, VALS_EDGES);
        else if (v == top) upd_vertical(u, top, x, VALS_EDGES);
        else {
            upd_vertical(u, top, x, VALS_EDGES);
            upd_vertical(v, top, x, 1);
        }
    }
    S get_vertical(int u, int ancestor, bool dont_get_ancestor) {
        S res = e();
        for (; head[u] != head[ancestor]; u = par[head[u]]) res = op(res, st.prod(pos[head[u]], pos[u] + 1));
        return op(res, st.prod(pos[ancestor] + dont_get_ancestor, pos[u] + 1));
    }
    S get(int u, int v) {
        if (u == v) return st.prod(pos[u], pos[u] + 1);
        int top = lca.get_lca(u, v);
        if (u == top) return get_vertical(v, top, VALS_EDGES);
        if (v == top) return get_vertical(u, top, VALS_EDGES);
        return op(get_vertical(u, top, VALS_EDGES), get_vertical(v, top, 1));
    }
}; // HeavyLightDecomposition
struct S_HLD { // segment
};
struct F_HLD { // lazy update
};
S_HLD op_hld(S_HLD l, S_HLD r) { // the combine operation for two segments
}
S_HLD mapping_hld(F_HLD l, S_HLD r) { // the update operation for a segment
}
F_HLD composition_hld(F_HLD l, F_HLD r) { // composition of two lazy updates (l is applied after r)
}
S_HLD e_hld() { return S_HLD(); } // the identity segment
F_HLD id_hld() { return F_HLD(); } // the identity update
template<bool VALS_EDGES> using HLD = 
    HeavyLightDecomposition<VALS_EDGES, S_HLD, op_hld, e_hld, F_HLD, mapping_hld, composition_hld, id_hld>;
