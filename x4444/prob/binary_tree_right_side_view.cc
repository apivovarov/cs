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

// Binary Tree Right Side View
class Solution {
 public:
  void visit(TreeNode *n, std::vector<int> &res, int level) {
    if (!n) return;
    // NRL
    if (res.size() <= level) {
      res.push_back(n->val);
    }
    visit(n->right, res, level + 1);
    visit(n->left, res, level + 1);
  }

  std::vector<int> rightSideView(TreeNode *root) {
    if (!root) return {};
    if (!root->left && !root->right) return {root->val};
    std::vector<int> res;
    visit(root, res, 0);
    return res;
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

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vv) {
  os << '[';
  for (int v : vv) os << v << ",";
  os << ']';
  return os;
}

void test(const std::vector<int> &inp, const std::vector<int> &expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  std::vector<int> res = sol.rightSideView(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, {});
  test({1}, {1});
  test({1, 2, 3}, {1, 3});
  test({1, N, 3}, {1, 3});
  test({1, 2, 3, N, 5, N, 4}, {1, 3, 4});
  test({1, 2, 3, 4, N, N, N, 5}, {1, 3, 4, 5});
}
