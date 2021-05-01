/**
 * Splay Tree
 * Binary Seach Tree
 * Time: amortized O(log(N))
 * Source: https://codeforces.com/blog/entry/18462
 */
template<typename K, typename V>
struct SplayTree {
    struct Node;

    Node *root = nullptr;
    int size = 0;

    ~SplayTree() {
        destroy(root);
    }

    void destroy(Node *cur) {
        if (!cur) return;
        destroy(cur->l);
        destroy(cur->r);
        delete cur;
    }

    void rotate_left(Node* cur) {
        Node *par = cur->p;
        Node *right = cur->r;
        Node *right_left = right->l;
        if (par) {
            if (cur == par->l) par->l = right;
            else par->r = right;
        }
        if (right_left) right_left->p = cur;
        cur->r = right_left;
        cur->p = right;
        right->l = cur;
        right->p = par;
    }

    void rotate_right(Node* cur) {
        Node *par = cur->p;
        Node *left = cur->l;
        Node *left_right = left->r;
        if (par) {
            if (cur == par->r) par->r = left;
            else par->l = left;
        }
        if (left_right) left_right->p = cur;
        cur->l = left_right;
        cur->p = left;
        left->r = cur;
        left->p = par;
    }

    void splay(Node* cur) {
        while (cur->p) {
            Node *par = cur->p;
            Node *grand = par->p;
            if (!grand) { // zig
                if (par->l == cur) rotate_right(par);
                else rotate_left(par);
            }
            else if (grand->l == par) {
                if (par->l == cur) { // zig-zig
                    rotate_right(grand);
                    rotate_right(par);
                }
                else { // zig-zag
                    rotate_left(par);
                    rotate_right(grand);
                }
            }
            else {
                if (par->r == cur) { // zig-zig
                    rotate_left(grand);
                    rotate_left(par);
                }
                else { // zig-zag
                    rotate_right(par);
                    rotate_left(grand);
                }
            }
        }
        root = cur;
    }

    void insert(K key, V val) {
        size++;
        if (!root) {
            root = new Node();
            root->k = key;
            root->v = val;
            return;
        }
        Node *cur = root;
        while (true) {
            if (key == cur->k) {
                cur->v = val;
                break;
            }
            if (key < cur->k) {
                if (cur->l) cur = cur->l;
                else {
                    cur->l = new Node();
                    cur->l->p = cur;
                    cur->l->k = key;
                    cur->l->v = val;
                    cur = cur->l;
                    break;
                }
            }
            else {
                if (cur->r) cur = cur->r;
                else {
                    cur->r = new Node();
                    cur->r->p = cur;
                    cur->r->k = key;
                    cur->r->v = val;
                    cur = cur->r;
                    break;
                }
            }
        }
        splay(cur);
    }

    Node* find(K key) {
        if (!root) return nullptr;
        Node *cur = root;
        while (true) {
            if (key == cur->k) break;
            if (key < cur->k) {
                if (cur->l) cur = cur->l;
                else break;
            }
            else {
                if (cur->r) cur = cur->r;
                else break;
            }
        }
        splay(cur);
        if (key == cur->k) return cur;
        return nullptr;
    }

    bool erase(K key) {
        Node *cur = find(key);
        if (!cur) return false;
        size--;
        Node *new_root = cur->left;
        if (!new_root) {
            root = cur->r;
            root->p = nullptr;
            delete cur;
            return true;
        }
        while (new_root->r) new_root = new_root->r;
        if (cur->r) {
            new_root->r = cur->r;
            cur->r->p = new_root;
        }
        root = cur->l;
        root->p = nullptr;
        delete cur;
        return true;
    }

    Node* first() {
        if (!root) return nullptr;
        Node *cur = root;
        while (cur->l) cur = cur->l;
        return cur;
    }

    Node* last() {
        if (!root) return nullptr;
        Node *cur = root;
        while (cur->r) cur = cur->r;
        return cur;
    }

// --------------------------------------
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Node *p = nullptr;
        K k;
        V v;
    };
// --------------------------------------
}; // SplayTree