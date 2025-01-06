#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// 222. Count Complete Tree Nodes
class Solution {
 public:
  int getHeight(TreeNode *n) {
    int h = 0;
    while (n->left) {
      ++h;
      n = n->left;
    }
    return h;
  }

  int countNodes(TreeNode *root) {
    if (!root) return 0;
    if (!root->left) return 1;
    if (!root->right) return 2;

    int hL = getHeight(root->left);
    int hR = getHeight(root->right);

    if (hL == hR) {
      // left tree is complete. L cnt = 2^(h-1)
      return (1 << (hL + 1)) - 1 + countNodes(root->right) + 1;
    } else {
      // right tree is complete. R cnt = 2^(h-1)
      return (1 << (hR + 1)) - 1 + countNodes(root->left) + 1;
    }
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

void test(const std::vector<int> &inp, int expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  int res = sol.countNodes(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, 0);
  test({1}, 1);
  test({1, 2, N}, 2);
  test({1, 2, 3}, 3);
  test({1, 2, 3, 4, N, N, N}, 4);
  test({1, 2, 3, 4, 5, N, N}, 5);
  test({1, 2, 3, 4, 5, 6, N}, 6);
  test({1, 2, 3, 4, 5, 6, 7}, 7);
  test({1, 2, 3, 4, 5, 6, 7, 8, N, N, N, N, N, N, N}, 8);
}
