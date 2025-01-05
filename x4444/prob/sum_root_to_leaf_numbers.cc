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

// 129. Sum Root to Leaf Numbers
class Solution {
 public:
  void visit(TreeNode *n, int curN, int &sum) {
    // NLR
    if (!n) return;
    curN *= 10;
    curN += n->val;
    if (!n->left && !n->right) sum += curN;
    visit(n->left, curN, sum);
    visit(n->right, curN, sum);
  }

  int sumNumbers(TreeNode *root) {
    int sum = 0;
    visit(root, 0, sum);
    return sum;
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
  int res = sol.sumNumbers(root);

  if (res != expected) {
    std::cerr << "ERROR:" << std::endl;
  }
  delTree(root);
}

int main() {
  test({}, 0);
  test({10}, 10);
  test({1, 2, 3}, 25);
  test({1, 2, N}, 12);
  test({1, N, 3}, 13);
  test({4, 9, 0, 5, 1, N, N}, 1026);
}
