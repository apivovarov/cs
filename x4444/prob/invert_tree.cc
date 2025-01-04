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
  void visit(TreeNode *n) {
    if (!n) return;
    visit(n->left);
    visit(n->right);
    auto tmp = n->left;
    n->left = n->right;
    n->right = tmp;
  }

  TreeNode *invertTree(TreeNode *root) {
    if (!root || (!root->left && !root->right)) return root;
    visit(root);
    return root;
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

bool isSame(TreeNode *p, TreeNode *q) {
  if (p == nullptr && q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;
  if (p->val != q->val) return false;
  if (!isSame(p->left, q->left)) return false;
  if (!isSame(p->right, q->right)) return false;
  return true;
}

void test(const std::vector<int> &vv, const std::vector<int> &expected) {
  TreeNode *root = makeTree(vv);
  TreeNode *expectedTree = makeTree(expected);
  Solution sol;
  TreeNode *root2 = sol.invertTree(root);

  if (!isSame(root2, expectedTree)) {
    std::cerr << "ERROR:" << std::endl;
  }
  delTree(root2);
  delTree(expectedTree);
}

int main() {
  test({}, {});
  test({10}, {10});
  test({10, 11, 12}, {10, 12, 11});
  test({4, 2, 7, 1, 3, 6, 9}, {4, 7, 2, 9, 6, 3, 1});
  test({4, 2, 7, 1, 3, 6, 9, 5, N, N, N, N, N, N, N},
       {4, 7, 2, 9, 6, 3, 1, N, N, N, N, N, N, N, 5});
}
