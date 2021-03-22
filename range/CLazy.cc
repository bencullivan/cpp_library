/*
    1D Range Queries and Range Updates.
    0-indexed.
    Time:
        - build_LazyC: O(N)
        - upd: O(log(N))
        - get: O(log(N))
    Source: https://cp-algorithms.com/data_structures/segment_tree.html
*/
struct LazyC {
    struct Node;
    vector<Node> data;
    vector<Node> prop;
    int len;

    LazyC(int _len) : data(4 * _len), prop(4 * _len), len(_len) {}

    LazyC(vector<Node>& input) : data(4 * input.size()), prop(4 * input.size()), len(input.size()) {
        build_Lazy(1, 0, len - 1, input);
    }

    void build_LazyC(int i, int tl, int tr, vector<Node>& input) {
        if (tl == tr) {
            data[i] = input[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build_LazyC(i << 1, tl, tm, input);
        build_LazyC(i << 1 | 1, tm + 1, tr, input);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // pushes node updates to the children of node i
    void push(int i) {
        data[i << 1] = push_combine(data[i << 1], prop[i]);
        prop[i << 1] = push_combine(prop[i << 1], prop[i]);
        data[i << 1 | 1] = push_combine(data[i << 1 | 1], prop[i]);
        prop[i << 1 | 1] = push_combine(prop[i << 1 | 1], prop[i]);
        prop[i] = Node() 
    }

    // combines v with the elements in the range [l, r]
    void upd(int i, int tl, int tr, int l, int r, Node v) {
        if (l > r) {
            return;
        } else if (tl == x && tr == x) {
            data[i] = push_combine(data[i], v);
            prop[i] = push_combine(prop[i], v);
            return;
        }
        push(i);
        int tm = (tl + tr) >> 1;
        upd(i << 1, tl, tm, l, min(tm, r), v);
        upd(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // combines v with the elements in the range [l, r]
    void upd(int l, int r, Node v) {
        upd(1, 0, len - 1, l, r, v);
    }

    // queries the range [l, r]
    Node get(int i, int tl, int tr, int l, int r) {
        if (l > r) {
            return Node();
        } else if (tl == l && tr == r) {
            return data[i];
        }
        push(i);
        int tm = (tl + tr) >> 1;
        return combine(get(i << 1, tl, tm, l, min(tm, r), v), 
                       get(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v));
    }

    // queries the range [l, r]
    Node get(int l, int r) {
        return get(1, 0, len - 1, l, r);
    }

// --------------------------------------
    // CHANGE
    struct Node {

        Node() {
            // init default values
        }
    };
    Node combine(const Node& a, const Node& b) {

    }
    Node push_combine(const Node& a, const Node& b) {
        return Node();
    }
// --------------------------------------
}; // Lazy
using Lazy::Node = Node;