/**
* Circular Doubly Linked List with a Sentinel
* Time:
*      - insert: O(1)
*      - erase: O(1)
*      - find: O(N)
* Source: me
*/
template<typename T>
struct LNode {
  T data;
  LNode *prev, *next;
  LNode() : prev(nullptr), next(nullptr) {}
  LNode(T _data) : data(_data), prev(nullptr), next(nullptr) {}
  LNode(T _data, LNode *_prev, LNode *_next) : data(_data), prev(_prev), next(_next) {}
};
template<typename T>
struct DLL {
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
  void insert_before(LNode<T> *new_node, LNode<T> *before) {
    new_node->prev = before->prev;
    before->prev->next = new_node;
    new_node->next = before;
    before->prev = new_node;
    len++;
  }

  // inserts the new node after the specified node
  void insert_after(LNode<T> *new_node, LNode<T> *after) {
    new_node->next = after->next;
    after->next->prev = new_node;
    new_node->prev = after;
    after->next = new_node;
    len++;
  }

  // removes the node from the list
  void erase(LNode<T> *to_erase) {
    assert(to_erase != sentinel);
    to_erase->next->prev = to_erase->prev;
    to_erase->prev->next = to_erase->next;
    delete to_erase;
    len--;
  }

  // returns a pointer to a node containing the specified value \
  // or nullptr if the specified value is not in the list
  LNode<T>* find(const T& val) {
    LNode<T>* cur = sentinel->next;
    while (cur != sentinel) {
      if (cur->data == val) {
        return cur;
      }
      cur = cur->next;
    }
    return nullptr;
  }
}; // DLL