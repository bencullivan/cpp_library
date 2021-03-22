/*
    1D Range Queries and Point Updates.
    0-indexed.
    Time: 
        - build_Segtree: O(N)
        - upd: O(log(N))
        - get: O(log(N))
    Source: https://cp-algorithms.com/data_structures/segment_tree.html
*/
struct Segtree {
    struct Node;
    vector<Node> data;
    int len;

    Segtree(int _len) : data(4 * _len), len(_len) {}

    Segtree(vector<Node>& input) : data(4 * input.size()), len(input.size()) {
        build_Segtree(1, 0, len - 1, input);
    }

    void build_Segtree(int i, int tl, int tr, vector<Node>& input) {
        if (tl == tr) {
            data[i] = input[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build_Segtree(i << 1, tl, tm, input);
        build_Segtree(i << 1 | 1, tm + 1, tr, input);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // sets the element at index x to v
    void upd(int i, int tl, int tr, int x, Node v) {
        if (tl == x && tr == x) {
            data[i] = v;
            return;
        }
        int tm = (tl + tr) >> 1;
        if (x <= tm) {
            upd(i << 1, tl, tm, x, v);
        } else {
            upd(i << 1 | 1, tm + 1, tr, x, v);
        }
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // sets the element at index x to v
    void upd(int x, Node v) {
        upd(1, 0, len - 1, x, v);
    }

    // queries the segment [l, r]
    Node get(int i, int tl, int tr, int l, int r) {
        if (l > r) {
            return Node();
        } else if (tl == l && tr == r) {
            return data[i];
        }
        int tm = (tl + tr) >> 1;
        return combine(get(i << 1, tl, tm, l, min(tm, r)), 
                       get(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r));
    }

    // queries the segment [l, r]
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
// --------------------------------------
}; // Segtree
using Node = Segtree::Node;