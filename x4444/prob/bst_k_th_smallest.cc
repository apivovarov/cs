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

// 230. Kth Smallest Element in a BST
class Solution {
 public:
  bool visit(TreeNode *n, int k, int &id, int &v) {
    if (!n) return false;
    // LNR
    if (visit(n->left, k, id, v)) return true;

    ++id;
    if (id == k) {
      v = n->val;
      return true;
    }

    if (visit(n->right, k, id, v)) return true;
    return false;
  }

  int kthSmallest(TreeNode *root, int k) {
    int v = -1;
    int id = 0;
    visit(root, k, id, v);
    return v;
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

void test(const std::vector<int> &inp, int k, int expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  int res = sol.kthSmallest(root, k);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({3, 1, 4, N, 2}, 1, 1);
  test({5, 3, 6, 2, 4, N, N, 1}, 3, 3);
}
