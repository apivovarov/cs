#include <ostream>

namespace x4444 {
namespace ds {

template <typename T>
struct Node {
  Node(const T& value_) : value(value_){};
  Node(const T& value_, Node<T>* parent_) : value(value_), parent(parent_){};
  T value;
  Node<T>* parent = nullptr;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
};

template <typename T>
class BST {
 protected:
  size_t sz = 0;
  Node<T>* root = nullptr;

  Node<T>* max_node(Node<T>* root_) const {
    if (root_ == nullptr) throw std::out_of_range("Tree is empty");
    Node<T>* curr_node = root_;
    while (true) {
      if (curr_node->right == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->right;
    }
  }

  Node<T>* min_node(Node<T>* root_) const {
    if (root_ == nullptr) throw std::out_of_range("Tree is empty");
    Node<T>* curr_node = root_;
    while (true) {
      if (curr_node->left == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->left;
    }
  }

  Node<T>* find_node(const T& v) const {
    Node<T>* curr_node = root;
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

  void _walk_iter(Node<T>* n, std::ostream& os) const {
    Node<T>* prev_ch = nullptr;
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

  void _walk_recurs(Node<T>* n, std::ostream& os) const {
    if (n == nullptr) {
      return;
    }
    _walk_recurs(n->left, os);
    os << n->value << ",";
    _walk_recurs(n->right, os);
  }

 public:
  size_t size() const { return sz; }

  T max() const { return max_node(root)->value; }

  T min() const { return min_node(root)->value; }

  bool contains(const T& v) const { return find_node(v) != nullptr; }

  void insert(const T& v) {
    if (root == nullptr) {
      root = new Node<T>(v);
      sz = 1;
      return;
    }
    Node<T>* curr_node = root;
    while (true) {
      if (curr_node->value == v) {
        return;
      }
      if (v < curr_node->value) {
        if (curr_node->left == nullptr) {
          curr_node->left = new Node<T>(v, curr_node);
          ++sz;
          break;
        } else {
          curr_node = curr_node->left;
        }
      } else {
        if (curr_node->right == nullptr) {
          curr_node->right = new Node<T>(v, curr_node);
          ++sz;
          break;
        } else {
          curr_node = curr_node->right;
        }
      }
    }
  }

  bool erase(const T& v) {
    Node<T>* n = find_node(v);
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
    Node<T>* max_left_node = max_node(n->left);
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
