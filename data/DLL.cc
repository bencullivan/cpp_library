/**
 * Circular Doubly Linked List with a Sentinel
 * Time:
 *      - insert: O(1)
 *      - erase: O(1)
 *      - find: O(N)
 * source: me
 */
template <typename T> struct LNode {
  T data;
  LNode *prev, *next;
  LNode() : prev(nullptr), next(nullptr) {}
  LNode(T _data) : data(_data), prev(nullptr), next(nullptr) {}
};
template <typename T> struct DLL {
  LNode<T> *sentinel;
  int len = 0;
  DLL() {
    sentinel = new LNode<T>();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
  }
  ~DLL() {
    while (sentinel->next != sentinel) {
      erase(sentinel->next);
    }
    delete sentinel;
  }
  // inserts the new node before the specified node
  void insert_before(LNode<T> *before, LNode<T> *new_node) {
    new_node->prev = before->prev;
    before->prev->next = new_node;
    new_node->next = before;
    before->prev = new_node;
    len++;
  }
  void insert_before(LNode<T> *before, const T &data) {
    insert_before(before, new LNode<T>(data));
  }
  // inserts the new node after the specified node
  void insert_after(LNode<T> *after, LNode<T> *new_node) {
    new_node->next = after->next;
    after->next->prev = new_node;
    new_node->prev = after;
    after->next = new_node;
    len++;
  }
  void insert_after(LNode<T> *after, const T &data) {
    insert_after(after, new LNode<T>(data));
  }
  // removes the node from the list
  void erase(LNode<T> *to_erase) {
    assert(to_erase != sentinel);
    to_erase->next->prev = to_erase->prev;
    to_erase->prev->next = to_erase->next;
    delete to_erase;
    len--;
  }
  // returns a pointer to a node containing the specified value
  // or nullptr if the specified value is not in the list
  LNode<T> *find(const T &val) {
    LNode<T> *cur = sentinel->next;
    while (cur != sentinel) {
      if (cur->data == val) {
        return cur;
      }
      cur = cur->next;
    }
    return nullptr;
  }
  int size() { return len; }
}; // DLL