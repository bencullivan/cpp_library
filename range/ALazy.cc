/*
    1D Range Queries and Range Assignments.
    0-indexed.
    Time:
        - build_LazyA: O(N)
        - upd: O(log(N))
        - get: O(log(N))
    Source: https://cp-algorithms.com/data_structures/segment_tree.html
*/
struct LazyA {
    struct Node;
    vector<Node> data;
    vector<bool> marked;
    int len;

    LazyA(int _len) : data(4 * _len), marked(4 * _len), len(_len) {}

    LazyA(vector<Node>& input) : data(4 * input.size()), marked(4 * input.size()), len(input.size()) {
        build_Lazy(1, 0, len - 1, input);
    }

    void build_LazyA(int i, int tl, int tr, vector<Node>& input) {
        if (tl == tr) {
            data[i] = input[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build_LazyA(i << 1, tl, tm, input);
        build_LazyA(i << 1 | 1, tm + 1, tr, input);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // pushes node updates to the children of node i
    void push(int i) {
        if (marked[i]) {
            data[i << 1] = data[i];
            marked[i << 1] = true;
            data[i << 1 | 1] = data[i];
            marked[i << 1 | 1] = true;
            marked[i] = false;
        }
    }

    // sets the elements in the range [l, r] to v
    void upd(int i, int tl, int tr, int l, int r, Node v) {
        if (l > r) {
            return;
        } else if (tl == l && tr == r) {
            data[i] = v;
            marked[i] = true;
            return;
        }
        push(i);
        int tm = (tl + tr) >> 1;
        upd(i << 1, tl, tm, l, min(tm, r), v);
        upd(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // sets the elements in the range [l, r] to v
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
        assign_get(1, 0, len - 1, l, r);
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
}; // LazyA
using LazyA::Node = Node;