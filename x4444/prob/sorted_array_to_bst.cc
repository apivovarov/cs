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

// 108. Convert Sorted Array to Binary Search Tree
class Solution {
  TreeNode *getRoot(int b, int e, const std::vector<int> &nums) {
    if (b >= e) return nullptr;
    if (e - b == 1) return new TreeNode(nums[b]);
    int m = b + (e - b) / 2;
    return new TreeNode(nums[m], getRoot(b, m, nums), getRoot(m + 1, e, nums));
  }

 public:
  TreeNode *sortedArrayToBST(const std::vector<int> &nums) {
    if (nums.empty()) return nullptr;
    if (nums.size() == 1) return new TreeNode(nums[0]);
    return getRoot(0, nums.size(), nums);
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

void test(const std::vector<int> &nums, const std::vector<int> &expected) {
  Solution sol;
  TreeNode *res = sol.sortedArrayToBST(nums);
  TreeNode *expTree = makeTree(expected);
  if (!isSame(res, expTree)) {
    std::cerr << "ERROR: not as expected";
  }
}

int main() {
  test({}, {});
  test({-10}, {-10});
  test({-10, -3, 0}, {-3, -10, 0});
  test({-10, -3, 0, 5, 9}, {0, -3, 9, -10, N, 5, N});
  test({-10, -5, -3, 0, 5, 8, 9}, {0, -5, 8, -10, -3, 5, 9});
}
