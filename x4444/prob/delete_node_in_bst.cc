#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  TreeNode* getMin(TreeNode* root) {
    while (root->left) {
      root = root->left;
    }
    return root;
  }

  TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else {
      if (!root->left) {
        TreeNode* tmp = root->right;
        root->right = nullptr;
        delete root;
        return tmp;
      } else if (!root->right) {
        TreeNode* tmp = root->left;
        root->left = nullptr;
        delete root;
        return tmp;
      } else {
        // both children
        TreeNode* rMin = getMin(root->right);
        root->val = rMin->val;
        root->right = deleteNode(root->right, rMin->val);
        return root;
      }
    }
    return root;
  }
};

int main() {
  TreeNode* l = new TreeNode(5);
  TreeNode* r = new TreeNode(15);
  TreeNode* n = new TreeNode(10, l, r);

  Solution sol;
  n = sol.deleteNode(n, 10);
  std::cerr << n->val << std::endl;
  n = sol.deleteNode(n, 1);
  std::cerr << n->val << std::endl;
  n = sol.deleteNode(n, 15);
  std::cerr << n->val << std::endl;
  n = sol.deleteNode(n, 5);
  std::cerr << n << std::endl;
}
