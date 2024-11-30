#include <queue>

namespace x4444::ds {

template <typename T>
struct Tree {
  struct Node {
    Node() = default;
    Node(const T& _value, Tree::Node* _left = nullptr,
         Tree::Node* _right = nullptr)
        : value(_value), left(_left), right(_right) {}
    T value;
    Tree::Node* left = nullptr;
    Tree::Node* right = nullptr;
  };

  Tree() = default;

  ~Tree() {
    dfs_postorder([](Tree::Node* n) { delete n; });
  }

  Tree::Node* root;

  template <class Callable>
  void __dfs_inorder(Tree::Node* n, Callable func) {
    if (!n) return;
    __dfs_inorder(n->left, func);
    func(n);
    __dfs_inorder(n->right, func);
  }

  template <class Callable>
  void __dfs_preorder(Tree::Node* n, Callable func) {
    if (!n) return;
    func(n);
    __dfs_preorder(n->left, func);
    __dfs_preorder(n->right, func);
  }

  template <class Callable>
  void __dfs_postorder(Tree::Node* n, Callable func) {
    if (!n) return;
    __dfs_postorder(n->left, func);
    __dfs_postorder(n->right, func);
    func(n);
  }

  template <class Callable>
  void dfs_inorder(Callable func) {
    __dfs_inorder(root, func);
  }

  template <class Callable>
  void dfs_preorder(Callable func) {
    __dfs_preorder(root, func);
  }

  template <class Callable>
  void dfs_postorder(Callable func) {
    __dfs_postorder(root, func);
  }

  template <class Callable>
  void bfs(Callable func) {
    if (!root) return;
    std::queue<Tree::Node*> q;
    q.push(root);
    while (!q.empty()) {
      auto* n = q.front();
      func(n);
      q.pop();
      if (n->left) q.push(n->left);
      if (n->right) q.push(n->right);
    }
  }
};
}  // namespace x4444::ds
