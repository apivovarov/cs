#include <iostream>
#include <unordered_map>

class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

  Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

  Node(int _val, Node* _left, Node* _right, Node* _next)
      : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
 public:
  void visit(Node* n, int level, std::unordered_map<int, Node*>& map) {
    // RLN, Reverse post-order traversal
    if (!n) return;
    visit(n->right, level + 1, map);
    visit(n->left, level + 1, map);
    auto it = map.find(level);
    if (it != map.end()) {
      n->next = it->second;
      it->second = n;
    } else {
      map.emplace(level, n);
    }
  }

  Node* connect(Node* root) {
    std::unordered_map<int, Node*> map;
    visit(root, 0, map);
    return root;
  }
};

void checkNext(const Node& n, Node* expected, const std::string& tag) {
  if (n.next != expected) {
    std::cerr << "ERROR: tag: " << tag << std::endl;
  }
}

int main() {
  Node n4(4);
  Node n5(5);
  Node n7(7);

  Node n2(2, &n4, &n5, nullptr);
  Node n3(3, nullptr, &n7, nullptr);

  Node n1(1, &n2, &n3, nullptr);

  Solution sol;
  sol.connect(&n1);

  checkNext(n1, nullptr, "n1");
  checkNext(n3, nullptr, "n3");
  checkNext(n7, nullptr, "n7");
  checkNext(n2, &n3, "n2");
  checkNext(n5, &n7, "n5");
  checkNext(n4, &n5, "n4");
}
