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

// Binary Tree Maximum Path Sum 
class Solution {
  int MIN = -1000000;

 public:
  void visit(TreeNode *n, int &sum, int &fsum) {
    // LRN
    if (!n) return;
    int l_sum = MIN;
    int l_fsum = MIN;
    visit(n->left, l_sum, l_fsum);

    int r_sum = MIN;
    int r_fsum = MIN;
    visit(n->right, r_sum, r_fsum);

    // Combinable sum - LN, RN, N
    sum = std::max(std::max(l_sum, r_sum), 0) + n->val;
    // Final sum - Lf, Rf, LNR. or sum if sum is larger
    fsum = std::max(std::max(std::max(l_fsum, r_fsum), l_sum + r_sum + n->val),
                    sum);
  }

  int maxPathSum(TreeNode *root) {
    if (!root) return 0;
    int sum = MIN;
    int fsum = MIN;
    visit(root, sum, fsum);
    return std::max(sum, fsum);
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
  int res = sol.maxPathSum(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  // test({5, 4, 8, 11, N, 13, 4, 7, 2, N, N, N, 1}, 22, true);
  test({1, 2, 3}, 6);
  test({1, 2, -3}, 3);
  test({1, -2, 3}, 4);
  test({-5, 2, 3}, 3);
  test({-13, 2, 3, 5, 6, 4, 1}, 13);
  test({-13, 2, 3, 5, 6, 4, 1, -2, -2, -3, -4, N, N, N, N}, 13);
  test({-13, 2, 3, 5, 6, 4, 1, -2, -2, -3, -4, -3, 0, 7, -5}, 15);
  test({5, 4, 8, 11, N, 13, 4, 7, 2, N, N, N, N, N, 1}, 48);
  test({-13, -9, -3, -5, -6, -4, -2}, -2);
}
