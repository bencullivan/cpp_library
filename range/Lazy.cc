struct Lazy {
    struct Node;
    bool assign;
    vector<Node> data;
    vector<Node> prop;
    vector<bool> marked;
    int len;

    Lazy(bool _assign, int _len) : assign(_assign), data(4 * _len), len(_len) {
        if (assign) {
            marked.resize(4 * len);
        } else {
            prop.resize(4 * len);
        }
    }

    Lazy(bool _assign, vector<Node>& input) : assign(_assign), data(4 * input.size()), len(input.size()) {
        if (assign) {
            marked.resize(4 * len);
        } else {
            prop.resize(4 * len);
        }
        build_Lazy(1, 0, len - 1, input);
    }

    void build_Lazy(int i, int tl, int tr, vector<Node>& input) {
        if (tl == tr) {
            data[i] = input[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build_Lazy(i << 1, tl, tm, input);
        build_Lazy(i << 1 | 1, tm + 1, tr, input);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // pushes node updates to the children of node i
    void assign_push(int i) {
        if (marked[i]) {
            data[i << 1] = data[i];
            marked[i << 1] = true;
            data[i << 1 | 1] = data[i];
            marked[i << 1 | 1] = true;
            marked[i] = false;
        }
    }

    // pushes node updates to the children of node i
    void combine_push(int i) {
        data[i << 1] = push_combine(data[i << 1], prop[i]);
        prop[i << 1] = push_combine(prop[i << 1], prop[i]);
        data[i << 1 | 1] = push_combine(data[i << 1 | 1], prop[i]);
        prop[i << 1 | 1] = push_combine(prop[i << 1 | 1], prop[i]);
        prop[i] = Node() 
    }

    // sets the elements in the range [l, r] to v
    void assign_upd(int i, int tl, int tr, int l, int r, Node v) {
        if (l > r) {
            return;
        } else if (tl == l && tr == r) {
            data[i] = v;
            marked[i] = true;
            return;
        }
        assign_push(i);
        int tm = (tl + tr) >> 1;
        assign_upd(i << 1, tl, tm, l, min(tm, r), v);
        assign_upd(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // combines v with the elements in the range [l, r]
    void combine_upd(int i, int tl, int tr, int l, int r, Node v) {
        if (l > r) {
            return;
        } else if (tl == x && tr == x) {
            data[i] = v;
            return;
        }
        combine_push(i);
        int tm = (tl + tr) >> 1;
        combine_upd(i << 1, tl, tm, l, min(tm, r), v);
        combine_upd(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
        data[i] = combine(data[i << 1], data[i << 1 | 1]);
    }

    // updates the range [l, r]
    void upd(int l, int r, Node v) {
        if (assign) {
            assign_upd(1, 0, len - 1, l, r, v);
        } else {
            combine_upd(1, 0, len - 1, l, r, v);
        }
    }

    // queries the range [l, r]
    Node assign_get(int i, int tl, int tr, int l, int r) {
        if (l > r) {
            return Node();
        } else if (tl == l && tr == r) {
            return data[i];
        }
        assign_push(i);
        int tm = (tl + tr) >> 1;
        return combine(assign_get(i << 1, tl, tm, l, min(tm, r), v), 
                       assign_get(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v));
    }

    // queries the range [l, r]
    Node combine_get(int i, int tl, int tr, int l, int r) {
        if (l > r) {
            return Node();
        } else if (tl == l && tr == r) {
            return data[i];
        }
        combine_push(i);
        int tm = (tl + tr) >> 1;
        return combine(combine_get(i << 1, tl, tm, l, min(tm, r), v), 
                       combine_get(i << 1 | 1, tm + 1, tr, max(tm + 1, l), r, v));
    }

    // queries the range [l, r]
    Node get(int l, int r) {
        if (assign) {
            return assign_get(1, 0, len - 1, l, r);
        } else {
            return combine_get(1, 0, len - 1, l, r);
        }
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