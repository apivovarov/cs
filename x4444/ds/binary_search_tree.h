#include <ostream>

namespace x4444 {
namespace ds {

template <typename T>
class BST {
 protected:
  struct Node {
    Node(const T& value_) : value(value_){};
    Node(const T& value_, Node* parent_) : value(value_), parent(parent_){};
    T value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
  };
  size_t sz = 0;
  Node* root = nullptr;

  static Node* max_node(Node* root_) {
    if (root_ == nullptr) throw std::out_of_range("MM: Tree is empty");
    Node* curr_node = root_;
    while (true) {
      if (curr_node->right == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->right;
    }
  }

  static Node* min_node(Node* root_) {
    if (root_ == nullptr) throw std::out_of_range("MI: Tree is empty");
    Node* curr_node = root_;
    while (true) {
      if (curr_node->left == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->left;
    }
  }

  Node* find_node(const T& v) const {
    Node* curr_node = root;
    while (true) {
      if (curr_node == nullptr) {
        return nullptr;
      }
      if (curr_node->value == v) {
        return curr_node;
      }
      if (v < curr_node->value) {
        curr_node = curr_node->left;
      } else {
        curr_node = curr_node->right;
      }
    }
  }

  void _walk_iter(Node* n, std::ostream& os) const {
    Node* prev_ch = nullptr;
    while (true) {
      if (n == nullptr) {
        return;
      }
      if (prev_ch != nullptr && prev_ch == n->right) {
        // just pop up from right
        // keep going up
        prev_ch = n;
        n = n->parent;
        continue;
      }
      if (prev_ch != nullptr && prev_ch == n->left) {
        // just pop up from left
        // skip go to left
      } else if (n->left != nullptr) {
        prev_ch = nullptr;
        n = n->left;
        continue;
      }
      os << n->value << ",";
      if (n->right != nullptr) {
        prev_ch = nullptr;
        n = n->right;
        continue;
      }
      prev_ch = n;
      n = n->parent;
    }
  }

  void _walk_recurs(Node* n, std::ostream& os) const {
    if (n == nullptr) {
      return;
    }
    _walk_recurs(n->left, os);
    os << n->value << ",";
    _walk_recurs(n->right, os);
  }

  void _del_postorder(Node* n) {
    if (!n) return;
    _del_postorder(n->left);
    _del_postorder(n->right);
    delete n;
  }

 public:
  ~BST() { _del_postorder(root); }

  class Iterator {
   public:
    Node* prev = nullptr;
    Node* curr = nullptr;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node* _prev, Node* _curr) : prev(_prev), curr(_curr){};

    reference operator*() const { return curr->value; }

    pointer operator->() const { return std::addressof(curr->value); }

    Iterator& operator++() {
      if (curr->right) {
        curr = min_node(curr->right);
        return *this;
      }
      auto* maybe_max = curr;
      auto* parent = curr->parent;
      while (parent) {
        if (curr == parent->left) {
          curr = parent;
          return *this;
        }
        curr = parent;
        parent = parent->parent;
      }
      prev = maybe_max;
      curr = nullptr;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator& operator--() {
      if (!curr) {
        curr = prev;
        return *this;
      }
      if (curr->left) {
        curr = max_node(curr->left);
        return *this;
      }
      auto* maybe_min = curr;
      auto* parent = curr->parent;
      while (parent) {
        if (curr == parent->right) {
          curr = parent;
          return *this;
        }
        curr = parent;
        parent = parent->parent;
      }
      prev = maybe_min;
      curr = maybe_min;
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const Iterator& other) const { return curr == other.curr; }

    bool operator!=(const Iterator& other) const { return curr != other.curr; }
  };

  Iterator begin() {
    auto* min_n = min_node(root);
    return Iterator(min_n, min_n);
  }

  Iterator end() { return Iterator(max_node(root), nullptr); }

  size_t size() const { return sz; }

  T max() const { return max_node(root)->value; }

  T min() const { return min_node(root)->value; }

  bool contains(const T& v) const { return find_node(v) != nullptr; }

  void insert(const T& v) {
    if (root == nullptr) {
      root = new Node(v);
      sz = 1;
      return;
    }
    Node* curr_node = root;
    while (true) {
      if (curr_node->value == v) {
        return;
      }
      if (v < curr_node->value) {
        if (curr_node->left == nullptr) {
          curr_node->left = new Node(v, curr_node);
          ++sz;
          break;
        } else {
          curr_node = curr_node->left;
        }
      } else {
        if (curr_node->right == nullptr) {
          curr_node->right = new Node(v, curr_node);
          ++sz;
          break;
        } else {
          curr_node = curr_node->right;
        }
      }
    }
  }

  bool erase(const T& v) {
    Node* n = find_node(v);
    if (n == nullptr) {
      return false;
    }
    // just one root node
    if (sz == 1) {
      root = nullptr;
      sz = 0;
      delete n;
      return true;
    }
    // leaf node
    if (n->left == nullptr && n->right == nullptr) {
      if (n == n->parent->left) {
        n->parent->left = nullptr;
      } else {
        n->parent->right = nullptr;
      }
      --sz;
      delete n;
      return true;
    }

    // one child (only right)
    if (n->left == nullptr) {
      if (n->parent == nullptr) {
        root = n->right;
      } else {
        if (n == n->parent->left) {
          n->parent->left = n->right;
        } else {
          n->parent->right = n->right;
        }
      }
      n->right->parent = n->parent;
      --sz;
      delete n;
      return true;
    }

    // one child (only left)
    if (n->right == nullptr) {
      if (n->parent == nullptr) {
        root = n->left;
      } else {
        if (n == n->parent->left) {
          n->parent->left = n->left;
        } else {
          n->parent->right = n->left;
        }
      }
      n->left->parent = n->parent;
      --sz;
      delete n;
      return true;
    }

    // merge left and right sub-trees
    Node* max_left_node = max_node(n->left);
    // detach max_left_node from its parent
    if (max_left_node->parent->left == max_left_node) {
      max_left_node->parent->left = max_left_node->left;
    } else {
      max_left_node->parent->right = max_left_node->left;
    }
    if (max_left_node->left != nullptr) {
      max_left_node->left->parent = max_left_node->parent;
    }
    // copy value from max_left_node to n
    n->value = std::move(max_left_node->value);
    --sz;
    delete max_left_node;
    return true;
  }

  void dump(std::ostream& os) const {
    os << "size: " << sz << std::endl;
    if (sz > 0) os << "root: " << root->value << std::endl;

    _walk_iter(root, os);
    os << std::endl;
  }
};

}  // namespace ds
}  // namespace x4444
