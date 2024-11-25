#include <iostream>
#include <ostream>

namespace x4444 {
namespace ds {

struct Node {
  Node(int value_) : value(value_){};
  Node(int value_, Node* parent_) : value(value_), parent(parent_){};
  int value;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
};

class BST {
 protected:
  int sz = 0;
  Node* root = nullptr;

  Node* max_node() const {
    if (root == nullptr) throw std::out_of_range("Tree is empty");
    Node* curr_node = root;
    while (true) {
      if (curr_node->right == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->right;
    }
  }

  Node* min_node() const {
    if (root == nullptr) throw std::out_of_range("Tree is empty");
    Node* curr_node = root;
    while (true) {
      if (curr_node->left == nullptr) {
        return curr_node;
      }
      curr_node = curr_node->left;
    }
  }

  Node* find_node(int v) const {
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

 public:
  int size() const { return sz; }

  int max() const { return max_node()->value; }

  int min() const { return min_node()->value; }

  bool contains(int v) const { return find_node(v) != nullptr; }

  void insert(int v) {
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

  void dump(std::ostream& os) const {
    _walk_iter(root, os);
    os << std::endl;
  }
};

}  // namespace ds
}  // namespace x4444

int main() {
  x4444::ds::BST t;
  t.insert(4);
  t.insert(1);
  t.insert(7);
  t.insert(9);
  t.insert(4);
  t.insert(5);
  t.insert(2);
  t.insert(9);
  t.insert(10);
  t.insert(3);
  t.insert(14);
  t.insert(21);
  t.insert(17);
  t.insert(16);
  t.insert(2);
  t.insert(14);

  t.dump(std::cerr);

  std::cout << "contains 55: " << std::boolalpha << t.contains(55) << std::endl;
  std::cout << "contains -55: " << std::boolalpha << t.contains(-55)
            << std::endl;
  std::cout << "contains 6: " << std::boolalpha << t.contains(6) << std::endl;
  std::cout << "contains 16: " << std::boolalpha << t.contains(16) << std::endl;
  std::cout << "contains 7: " << std::boolalpha << t.contains(7) << std::endl;

  std::cout << "max: " << t.max() << std::endl;
  std::cout << "min: " << t.min() << std::endl;

  std::cout << "size: " << t.size() << std::endl;
}
