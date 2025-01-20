#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  TreeNode *searchBST(TreeNode *root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) {
      return searchBST(root->left, val);
    } else {
      return searchBST(root->right, val);
    }
  }
};

int main() {
  TreeNode l(5);
  TreeNode r(15);
  TreeNode n(10, &l, &r);

  Solution sol;
  std::cerr << sol.searchBST(&n, 10)->val << std::endl;
  std::cerr << sol.searchBST(&n, 5)->val << std::endl;
  std::cerr << sol.searchBST(&n, 15)->val << std::endl;
  std::cerr << sol.searchBST(&n, 1) << std::endl;
}
