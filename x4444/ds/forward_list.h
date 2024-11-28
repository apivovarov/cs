#include <ostream>
#include <utility>
#include <iterator>

namespace x4444 {
namespace ds {

template <typename T>
class ForwardList {
 protected:
  struct Node {
    Node(const T& _value, Node* _next) : value(_value), next(_next) {}
    Node(T&& _value, Node* _next) : value(std::move(_value)), next(_next) {}
    T value;
    Node* next = nullptr;
  };
  Node* root = nullptr;

 public:
  class Iterator {
   protected:
    Node* curr;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node* n) : curr(n) {}

    reference operator*() const { return curr->value; }

    pointer operator->() const { return std::addressof(curr->value); }

    Iterator& operator++() {
      if (curr) curr = curr->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const Iterator& other) const { return curr == other.curr; }

    bool operator!=(const Iterator& other) const { return curr != other.curr; }
  };

  class ConstIterator {
   protected:
    Node* curr;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstIterator(Node* n) : curr(n) {}

    reference operator*() const { return curr->value; }

    pointer operator->() const { return std::addressof(curr->value); }

    ConstIterator& operator++() {
      if (curr) curr = curr->next;
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIterator& other) const {
      return curr == other.curr;
    }

    bool operator!=(const ConstIterator& other) const {
      return curr != other.curr;
    }
  };

  ~ForwardList() {
    while (root) {
      Node* tmp = root;
      root = root->next;
      delete tmp;
    }
  }

  Iterator begin() { return Iterator(root); }
  ConstIterator begin() const { return ConstIterator(root); }
  ConstIterator cbegin() { return ConstIterator(root); }

  Iterator end() { return Iterator(nullptr); }
  ConstIterator end() const { return ConstIterator(nullptr); }
  ConstIterator cend() { return ConstIterator(nullptr); }

  T& front() {
    if (!root) throw std::out_of_range("Forward List is empty");
    return root->value;
  }

  const T& front() const {
    if (!root) throw std::out_of_range("Forward List is empty");
    return root->value;
  }

  void push_front(const T& v) { root = new ForwardList::Node(v, root); }

  void push_front(T&& v) { root = new ForwardList::Node(std::move(v), root); }

  void pop_front() {
    if (!root) throw std::out_of_range("Forward List is empty");
    Node* tmp = root;
    root = root->next;
    delete tmp;
  }

  size_t remove(const T& v) {
    size_t cnt = 0;
    Node* n = root;
    Node* prev = nullptr;
    while (n) {
      if (n->value == v) {
        if (prev) {
          prev->next = n->next;
        }
        auto* tmp = n;
        n = n->next;
        if (tmp == root) {
          root = n;
        }
        delete tmp;
        ++cnt;
      } else {
        prev = n;
        n = n->next;
      }
    }
    return cnt;
  }

  void dump(std::ostream& os) {
    Node* n = root;
    while (n) {
      os << n->value << " ";
      n = n->next;
    }
    os << std::endl;
  }
};
}  // namespace ds
}  // namespace x4444
