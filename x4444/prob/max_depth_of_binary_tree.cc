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

void delTree(TreeNode *n) {
  if (!n) return;
  delTree(n->left);
  delTree(n->right);
  delete (n);
}

class Solution {
 public:
  int visit(TreeNode *n, int level) {
    if (!n) return level;
    int a = visit(n->left, level + 1);
    int b = visit(n->right, level + 1);
    return a < b ? b : a;
  }

  int maxDepth(TreeNode *root) {
    if (!root) return 0;
    return visit(root, 0);
  }
};

#include <limits>
constexpr int N = std::numeric_limits<int>::min();

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

void test(const std::vector<int> &vv, int expected) {
  TreeNode *root = makeTree(vv);
  Solution sol;
  int res = sol.maxDepth(root);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expe: " << expected << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, 0);
  test({10}, 1);
  test({3, 9, 20, N, N, 15, 7, N, N, N, N, N, N, 4, N}, 4);
}
