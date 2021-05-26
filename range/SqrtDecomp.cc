// Sqrt Decomposition
// Time: 
// 	- build: O(N)
// 	- upd: O(sqrt(N))
// 	- get: O(sqrt(N))
// Source: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
struct SqrtDecomp {
  struct Node;
  struct Lazy;
  vector<Node> data;
  vector<Node> segs;
  vector<Lazy> lazy;
  int len, root;

  SqrtDecomp(int _len) data(_len), len(_len), root(sqrt(_len) + 1) {
    segs.resize(root);
    lazy.resize(root);
  }

  void build() {
    for (int i = 0; i < len; i++) {
      absorb(segs[i / root], data[i]);
    }
  }
  
  // updates the range [l, r]
  void upd(int l, int r, const Lazy& lz) {
    int lseg = l / root;
    int rseg = r / root;
    if (lseg == rseg) {
      for (int i = l; i <= r; i++) {
        data[i] = lazy_combine(data[i], lz);
        segs[lseg] = lazy_combine(segs[lseg], lz);
      }
      return;
    }
    for (int i = l; i <= (lseg + 1) * root - 1; i++) {
      data[i] = lazy_combine(data[i], lz);
      segs[lseg] = lazy_combine(segs[lseg], lz);
    }
    for (int i = lseg + 1; i < rseg; i++) {
      lazy_absorb(lazy[i], lz);
    }
    for (int i = rseg * root; i <= r; i++) {
      data[i] = lazy_combine(data[i], lz);
      segs[rseg] = lazy_combine(segs[rseg], lz);
    }
  }

  // queries the range [l,r]
  Node get(int l, int r) {
    Node ans;
    int lseg = l / root;
    int rseg = r / root;
    if (lseg == rseg) {
      for (int i = l; i <= r; i++) {
        absorb(ans, lazy_combine(data[i], lazy[lseg]));
      }
      return ans;
    }
    for (int i = l; i <= (lseg + 1) * root - 1; i++) {
      absorb(ans, lazy_combine(data[i], lazy[lseg]));
    }
    for (int i = lseg + 1; i < rseg; i++) {
      absorb(ans, segs[i]);
    }
    for (int i = rseg * root; i <= r; i++) {
      absorb(ans, lazy_combine(data[i], lazy[rseg]));
    }
    return ans;
  }

// --------------------------------------
  // CHANGE
  struct Node {
    ll v = 0;
  };
  Node combine(const Node& a, const Node& b) {

  }
  void absorb(Node& a, const Node& b) {

  }

  struct Lazy {
    ll v;
  };
  Node lazy_combine(const Node& a, const Lazy& b) {

  }
  void lazy_absorb(Lazy& a, const Lazy& b) {

  }
// --------------------------------------
}; // SqrtDecomp
using Node = SqrtDecomp::Node;