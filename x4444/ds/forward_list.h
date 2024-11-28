#include <ostream>
#include <utility>

namespace x4444 {
namespace ds {

template <typename T>
class ForwardList {
 protected:
  //template <typename K>
  struct Node {
    Node(const T& _value, Node* _next) : value(_value), next(_next) {}
    Node(T&& _value, Node* _next) : value(std::move(_value)), next(_next) {}
    T value;
    Node* next = nullptr;
  };
  Node* root = nullptr;

 public:
  T& front() {
    if (!root) throw std::out_of_range("Forward List is empty");
    return root->value;
  }

  const T& front() const {
    if (!root) throw std::out_of_range("Forward List is empty");
    return root->value;
  }

  void push_front(const T& v) {
    root = new ForwardList::Node(v, root);
    ;
  }

  void push_front(T&& v) {
    root = new ForwardList::Node(std::move(v), root);
  }

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
