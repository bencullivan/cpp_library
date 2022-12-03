// not tested
template <typename T> struct SkipList {
  std::mt19937 sl_rng;
  int flip() { return std::uniform_int_distribution<int>(0, 1)(sl_rng); }
  struct node {
    bool ih;
    T data;
    node *pr, *nx, *lo, *hi;
    node()
        : ih(1), data(T()), pr(nullptr), nx(nullptr), lo(nullptr), hi(nullptr) {
    }
    node(const T &t)
        : ih(0), data(t), pr(nullptr), nx(nullptr), lo(nullptr), hi(nullptr) {}
  };
  node *root;
  int h, s;
  SkipList()
      : sl_rng(std::chrono::high_resolution_clock::now()
                   .time_since_epoch()
                   .count()),
        root(new node()), h(1), s(0) {}
  void destroyLevel(node *cur) {
    if (cur) {
      destroyLevel(cur->nx);
      delete cur;
    }
  }
  void destroy(node *head) {
    if (head) {
      destroy(head->lo);
      destroyLevel(head);
    }
  }
  ~SkipList() { destroy(root); }
  node *find(const T &t) {
    node *cur = root;
    while (cur->lo) {
      cur = cur->lo;
      while (cur->nx && t >= cur->nx->data) {
        cur = cur->nx;
      }
    }
    return cur;
  }
  void newLevel() {
    node *nh = new node();
    if (root->lo) {
      root->lo->hi = nh;
    }
    nh->lo = root->lo;
    nh->hi = root;
    root->lo = nh;
  }
  void insertAfter(node *pr, node *lo, const T &t) {
    node *nw = new node(t);
    if (pr->nx) {
      pr->nx->pr = nw;
    }
    nw->nx = pr->nx;
    pr->nx = nw;
    nw->lo = lo;
    lo->hi = nw;
  }
  node *insert(const T &t) {
    node *cur = find(t);
    node *last = nullptr;
    int i = 1;
    do {
      i++;
      if (i >= h) {
        h++;
        newLevel();
      }
      while (!cur->hi) {
        cur = cur->pr;
      }
      cur = cur->hi;
      insertAfter(cur, last, t);
      last = cur->nx;
    } while (flip());
    s++;
    return last;
  }
  bool erase(const T &t) {
    node *cur = find(t);
    if (cur->ih || cur->data != t) {
      return 0;
    }
    while (cur) {
      node *hi = cur->hi;
      if (cur->pr) {
        cur->pr->nx = cur->nx;
      }
      if (cur->nx) {
        cur->nx->pr = cur->pr;
      }
      delete cur;
      cur = hi;
    }
    s--;
    return 1;
  }
  int size() { return s; }
};