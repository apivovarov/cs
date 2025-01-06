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

// 637. Average of Levels in Binary Tree
class Solution {
 public:
  void visit(TreeNode *n, std::vector<double> &sums, std::vector<int> &cnts,
             int level) {
    if (!n) return;
    // NLR
    if (sums.size() <= level) {
      sums.push_back(double(n->val));
      cnts.push_back(1);
    } else {
      sums[level] += double(n->val);
      ++cnts[level];
    }
    visit(n->left, sums, cnts, level + 1);
    visit(n->right, sums, cnts, level + 1);
  }

  std::vector<double> averageOfLevels(TreeNode *root) {
    if (!root) return {};
    if (!root->left && !root->right) return {double(root->val)};
    std::vector<double> sums;
    std::vector<int> cnts;
    visit(root, sums, cnts, 0);
    for (int i = 0; i < sums.size(); ++i) {
      sums[i] /= cnts[i];
    }
    return sums;
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

std::ostream &operator<<(std::ostream &os, const std::vector<double> &vv) {
  os << '[';
  for (auto v : vv) os << v << ",";
  os << ']';
  return os;
}

void test(const std::vector<int> &inp, const std::vector<double> &expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  std::vector<double> res = sol.averageOfLevels(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, {});
  test({1}, {1.});
  test({1, 2, 3}, {1., 2.5});
  test({1, N, 3}, {1., 3.});
  test({1, 2, 3, N, 5, N, 4}, {1, 2.5, 4.5});
  test({1, 2, 3, 4, N, N, N, 5}, {1, 2.5, 4., 5.});
  test({3, 9, 20, N, N, 15, 7}, {3., 14.5, 11.});
  test({3, 9, 20, 15, 7}, {3., 14.5, 11.});
}
