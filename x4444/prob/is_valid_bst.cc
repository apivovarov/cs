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

// 98. Validate Binary Search Tree
class Solution {
 public:
  bool visit(TreeNode *n, int &prevV, bool &init) {
    if (!n) return true;
    // LNR
    if (!visit(n->left, prevV, init)) return false;

    if (init) {
      if (prevV >= n->val) return false;
    } else {
      init = true;
    }
    prevV = n->val;

    if (!visit(n->right, prevV, init)) return false;
    return true;
  }

  bool isValidBST(TreeNode *root) {
    int prevV = 0;
    bool init = false;
    bool res = visit(root, prevV, init);
    return res;
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

void test(const std::vector<int> &inp, bool expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  bool res = sol.isValidBST(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({2, 1, 3}, true);
  test({5, 1, 4, N, N, 3, 6}, false);
}
