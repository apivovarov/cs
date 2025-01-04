#include <iostream>

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
  bool visit(TreeNode *n1, TreeNode *n2) {
    if (!n1 && !n2) return true;
    if (!n1 || !n2) return false;
    if (n1->val != n2->val) return false;
    if (!visit(n1->left, n2->right)) return false;
    if (!visit(n1->right, n2->left)) return false;
    return true;
  }

  bool isSymmetric(TreeNode *root) {
    if (!root) return true;
    return visit(root->left, root->right);
  }
};

#include <limits>
constexpr int N = std::numeric_limits<int>::min();

void delTree(TreeNode *n) {
  if (!n) return;
  delTree(n->left);
  delTree(n->right);
  delete (n);
}

TreeNode *makeTree(const std::vector<int> &vv) {
  if (vv.empty()) return nullptr;
  std::vector<TreeNode *> nv;
  nv.reserve(vv.size());
  nv.push_back(new TreeNode(vv[0]));
  for (int i = 1; i < vv.size(); ++i) {
    if (vv[i] == N) {
      nv.push_back(nullptr);
    } else {
      nv.push_back(new TreeNode(vv[i]));
    }
    int pid = (i - 1) / 2;
    if (nv[pid]) {
      if (i % 2 == 0) {
        nv[pid]->right = nv[i];
      } else {
        nv[pid]->left = nv[i];
      }
    }
  }
  return nv[0];
}

void test(const std::vector<int> &vv, bool expected) {
  TreeNode *root = makeTree(vv);
  Solution sol;
  bool res = sol.isSymmetric(root);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expe: " << expected << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, true);
  test({10}, true);
  test({10, 5, 5}, true);
  test({10, 5, 4}, false);
  test({10, 5, 5, 1, 2, 2, 1}, true);
  test({10, 5, 5, 1, 2, 1, 2}, false);
  test({10, 5, 5, 1, N, N, 1}, true);
  test({10, 5, 5, 1, N, 1, N}, false);
  test({1, 2, 2, 3, 4, 4, 3}, true);
  test({1, 2, 2, N, 3, N, 3}, false);
}
