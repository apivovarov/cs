#include <iostream>
#include <vector>
#include <unordered_map>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// Path Sum III
class Solution {
 public:
  void visit(TreeNode *root, int targetSum,
             std::unordered_map<long, int> &prefixSumMap, long prefixSum,
             int &cnt) {
    if (!root) return;
    prefixSum += root->val;
    auto it = prefixSumMap.find(prefixSum - targetSum);
    if (it != prefixSumMap.end()) {
      cnt += it->second;
    }
    ++prefixSumMap[prefixSum];
    visit(root->left, targetSum, prefixSumMap, prefixSum, cnt);
    visit(root->right, targetSum, prefixSumMap, prefixSum, cnt);
    --prefixSumMap[prefixSum];
  }

  int pathSum(TreeNode *root, int targetSum) {
    int cnt = 0;
    std::unordered_map<long, int> prefixSumMap;
    ++prefixSumMap[0];
    visit(root, targetSum, prefixSumMap, 0, cnt);
    return cnt;
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

void test(const std::vector<int> &inp, int targetSum, int expected) {
  TreeNode *root = makeTree(inp);
  Solution sol;
  int res = sol.pathSum(root, targetSum);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
  delTree(root);
}

int main() {
  test({5, 4, 8, 11, N, 13, 4, 7, 2, N, N, N, 1}, 22, 3);
  test({1, 2, 3}, 5, 0);
  test({1, N, 3}, 4, 1);
  test({}, 5, 0);
  test({}, 0, 0);
  test({10}, 10, 1);
  test({10}, 9, 0);
  test({10, 5, -3, 3, 2, N, 11, 3, -2, N, 1}, 8, 3);
  test({1, 0, 1, 1, 2, 0, -1, 0, 1, -1, 0, -1, 0, 1, 0}, 2, 13);
}
