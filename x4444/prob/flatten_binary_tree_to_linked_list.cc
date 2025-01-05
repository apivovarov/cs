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

// Flatten Binary Tree to Linked List
class Solution {
 public:
  void visit(TreeNode *n, TreeNode *&prev) {
    // RLN , Reverse post-order
    if (!n) return;
    visit(n->right, prev);
    visit(n->left, prev);
    n->right = prev;
    n->left = nullptr;
    prev = n;
  }

  void flatten(TreeNode *root) {
    TreeNode *prev = nullptr;
    visit(root, prev);
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

void test(const std::vector<int> &inp, const std::vector<int> &expected) {
  TreeNode *root = makeTree(inp);
  TreeNode *expectedTree = makeTree(expected);
  Solution sol;
  sol.flatten(root);

  if (!isSame(root, expectedTree)) {
    std::cerr << "ERROR:" << std::endl;
  }
  delTree(root);
  delTree(expectedTree);
}

int main() {
  std::vector<int> expected = {1, N, 2, N, N, N, 3};
  expected.insert(expected.end(), {N, N, N, N, N, N, N, 4});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, N});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, 5});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, N});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, N});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, N});
  expected.insert(expected.end(), {N, N, N, N, N, N, N, 6});
  test({1, 2, 5, 3, 4, N, 6}, expected);
}
