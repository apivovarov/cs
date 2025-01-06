#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Lowest Common Ancestor of a Binary Tree
class Solution {
 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root) return root;
    if (root == p || root == q) return root;
    TreeNode *L = lowestCommonAncestor(root->left, p, q);
    TreeNode *R = lowestCommonAncestor(root->right, p, q);
    if (L && R) return root;
    if (L) return L;
    return R;
  }
};

class Solution2 {
  void visit(TreeNode *n, std::vector<TreeNode *> &st0,
             std::vector<TreeNode *> &st1, int v0, int v1, bool &v0found,
             bool &v1found) {
    // NLR
    if (!n) return;
    if (v0found && v1found) return;

    if (!v0found) {
      st0.push_back(n);
      if (v0 == n->val) {
        v0found = true;
      }
    }

    if (!v1found) {
      st1.push_back(n);
      if (v1 == n->val) {
        v1found = true;
      }
    }
    if (v0found && v1found) return;
    visit(n->left, st0, st1, v0, v1, v0found, v1found);
    if (v0found && v1found) return;
    visit(n->right, st0, st1, v0, v1, v0found, v1found);
    if (!v0found) {
      st0.pop_back();
    }
    if (!v1found) {
      st1.pop_back();
    }
  }

 public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root) return root;
    if (!root->left && !root->right) return root;
    if (root->val == p->val || root->val == q->val) return root;
    std::vector<TreeNode *> st0;
    std::vector<TreeNode *> st1;
    bool v0found;
    bool v1found;
    visit(root, st0, st1, p->val, q->val, v0found, v1found);
    int sz = std::min(st0.size(), st1.size());
    for (int i = 0; i < sz; ++i) {
      if (st0[i] != st1[i]) return st0[i - 1];
    }
    return st0[sz - 1];
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

std::vector<TreeNode *> makeTreeVec(const std::vector<int> &vv) {
  if (vv.empty()) return {};
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
  return nv;
}

void test(const std::vector<int> &inp, int a, int b, int expected) {
  std::vector<TreeNode *> nv = makeTreeVec(inp);
  TreeNode *root = nv[0];
  Solution sol;
  TreeNode *aNp = nullptr;
  TreeNode *bNp = nullptr;
  for (TreeNode *p : nv) {
    if (!p) continue;
    if (aNp && bNp) break;
    if (p->val == a) aNp = p;
    if (p->val == b) bNp = p;
  }

  TreeNode *resN = sol.lowestCommonAncestor(root, aNp, bNp);
  int res = resN->val;
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({1, 2, 3}, 2, 3, 1);
  test({1, 2, N}, 1, 2, 1);
  test({1, N, 3}, 1, 3, 1);
  test({1, 2, 3, 4, 5, 6, 7}, 2, 3, 1);
  test({1, 2, 3, 4, 5, 6, 7}, 2, 5, 2);
  test({1, 2, 3, 4, 5, 6, 7}, 1, 5, 1);
  test({1, 2, 3, 4, 5, 6, 7}, 5, 6, 1);
  test({3, 5, 1, 6, 2, 0, 8, N, N, 7, 4}, 5, 1, 3);
}
