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
  bool visit(TreeNode *n, int targetSum, int curSum) {
    // NLR
    if (!n) return false;
    curSum += n->val;
    if (curSum == targetSum && !n->left && !n->right) return true;
    if (visit(n->left, targetSum, curSum)) return true;
    if (visit(n->right, targetSum, curSum)) return true;
    return false;
  }

  bool hasPathSum(TreeNode *root, int targetSum) {
    if (!root) return false;
    return visit(root, targetSum, 0);
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

bool isSame(TreeNode *p, TreeNode *q) {
  if (p == nullptr && q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;
  if (p->val != q->val) return false;
  if (!isSame(p->left, q->left)) return false;
  if (!isSame(p->right, q->right)) return false;
  return true;
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

void test(const std::vector<int> &inp, int targetSum, bool expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  bool res = sol.hasPathSum(root, targetSum);

  if (res != expected) {
    std::cerr << "ERROR:" << std::endl;
  }
  delTree(root);
}

int main() {
  test({5, 4, 8, 11, N, 13, 4, 7, 2, N, N, N, 1}, 22, true);
  test({1, 2, 3}, 5, false);
  test({1, N, 3}, 4, true);
  test({}, 5, false);
  test({}, 0, false);
  test({10}, 10, true);
  test({10}, 9, false);
}
