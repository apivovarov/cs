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

// 530. Minimum Absolute Difference in BST
class Solution {
 public:
  bool visit(TreeNode *n, int &prev, int &diff) {
    if (!n) return false;
    // LNR
    if (visit(n->left, prev, diff)) return true;
    int _diff = std::abs(prev - n->val);
    prev = n->val;
    if (_diff < diff) diff = _diff;
    if (_diff <= 1) return true;
    if (visit(n->right, prev, diff)) return true;
    return false;
  }
  int getMinimumDifference(TreeNode *root) {
    if (!root) return 0;
    int prev = -1000000;
    int diff = 1000000;
    visit(root, prev, diff);
    return diff;
  }
};

#include <limits>
#include <vector>
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

void test(const std::vector<int> &inp, int expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  int res = sol.getMinimumDifference(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({10, 5, 13}, 3);
  test({4, 2, 6, 1, 3}, 1);
  test({4, 2, 6, 1, 3}, 1);
  test({1, 0, 48, N, N, 12, 49}, 1);
  test({1, 0, 48, N, N, 12, 49}, 1);
}
