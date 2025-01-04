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
  bool visit(TreeNode *p, TreeNode *q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;
    if (p->val != q->val) return false;
    if (!visit(p->left, q->left)) return false;
    if (!visit(p->right, q->right)) return false;
    return true;
  }

  bool isSameTree(TreeNode *p, TreeNode *q) { return visit(p, q); }
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

void test(const std::vector<int> &vv, const std::vector<int> &vv2,
          bool expected) {
  TreeNode *root = makeTree(vv);
  TreeNode *root2 = makeTree(vv2);
  Solution sol;
  bool res = sol.isSameTree(root, root2);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expe: " << expected << std::endl;
  }
  delTree(root);
  delTree(root2);
}

int main() {
  test({}, {}, true);
  test({}, {10}, false);
  test({10}, {}, false);
  test({10}, {10}, true);
  test({10}, {9}, false);
  test({3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 4, N},
       {3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 4, N}, true);
  test({3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 4, N},
       {3, 9, 20, 3, N, 15, 7, N, N, N, N, N, N, 4, N}, false);
  test({3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 4, N},
       {3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 5, N}, false);
}
