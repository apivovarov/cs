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

// 103. Binary Tree Zigzag Level Order Traversal
class Solution {
 public:
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode *root) {
    if (!root) return {};
    std::vector<std::vector<int>> res;
    std::vector<TreeNode *> st0 = {root};
    std::vector<TreeNode *> st1;
    int level = 0;

    while (true) {
      if (level % 2 == 0) {
        if (st0.empty()) break;
        res.push_back({});
        while (!st0.empty()) {
          TreeNode *n = st0.back();
          st0.pop_back();
          res[level].push_back(n->val);
          if (n->left) st1.push_back(n->left);
          if (n->right) st1.push_back(n->right);
        }
      } else {
        if (st1.empty()) break;
        res.push_back({});
        while (!st1.empty()) {
          TreeNode *n = st1.back();
          st1.pop_back();
          res[level].push_back(n->val);
          if (n->right) st0.push_back(n->right);
          if (n->left) st0.push_back(n->left);
        }
      }
      ++level;
    }
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

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void test(const std::vector<int> &inp,
          const std::vector<std::vector<int>> &expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  std::vector<std::vector<int>> res = sol.zigzagLevelOrder(root);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, {});
  test({1}, {{1}});
  test({1, 2, 3}, {{1}, {3, 2}});
  test({1, N, 3}, {{1}, {3}});
  test({1, 2, 3, N, 5, N, 4}, {{1}, {3, 2}, {5, 4}});
  test({1, 2, 3, 4, N, N, N, 5}, {{1}, {3, 2}, {4}, {5}});
  test({3, 9, 20, N, N, 15, 7}, {{3}, {20, 9}, {15, 7}});
  test({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
       {{1}, {3, 2}, {4, 5, 6, 7}, {15, 14, 13, 12, 11, 10, 9, 8}});
}
