#include <iostream>
#include <vector>
#include <unordered_set>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  TreeNode *visit(int &id, const std::unordered_map<int, int> &inorder_v_id,
                  const std::vector<int> &postorder, int inb, int ine) {
    if (id == 0 || inb >= ine) return nullptr;
    int rootV = postorder[id - 1];
    --id;
    TreeNode *root = new TreeNode(rootV);
    if (id == 0) return root;
    int k = inorder_v_id.at(rootV);
    root->right = visit(id, inorder_v_id, postorder, k + 1, ine);
    root->left = visit(id, inorder_v_id, postorder, inb, k);
    return root;
  }

  TreeNode *buildTree(const std::vector<int> &inorder,
                      const std::vector<int> &postorder) {
    if (postorder.empty()) return nullptr;
    if (postorder.size() == 1) return new TreeNode(postorder[0]);

    std::unordered_map<int, int> inorder_v_id;
    for (int i = 0; i < inorder.size(); ++i) {
      inorder_v_id.emplace(inorder[i], i);
    }
    int id = postorder.size();
    return visit(id, inorder_v_id, postorder, 0, inorder.size());
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

bool isSame(TreeNode *p, TreeNode *q) {
  if (p == nullptr && q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;
  if (p->val != q->val) return false;
  if (!isSame(p->left, q->left)) return false;
  if (!isSame(p->right, q->right)) return false;
  return true;
}

void test(const std::vector<int> &inorder, const std::vector<int> &postorder,
          const std::vector<int> &expected) {
  TreeNode *expectedTree = makeTree(expected);
  Solution sol;
  TreeNode *root2 = sol.buildTree(inorder, postorder);

  if (!isSame(root2, expectedTree)) {
    std::cerr << "ERROR:" << std::endl;
  }
  delTree(root2);
  delTree(expectedTree);
}

int main() {
  test({-1}, {-1}, {-1});
  test({10}, {10}, {10});
  test({5, 10, 15}, {5, 15, 10}, {10, 5, 15});
  test({5, 10}, {5, 10}, {10, 5, N});
  test({10, 15}, {15, 10}, {10, N, 15});
  test({3, 5, 10}, {3, 5, 10}, {10, 5, N, 3, N, N, N});
  test({5, 6, 10}, {6, 5, 10}, {10, 5, N, N, 6, N, N});
  test({10, 13, 15}, {13, 15, 10}, {10, N, 15, N, N, 13, N});
  test({10, 15, 16}, {16, 15, 10}, {10, N, 15, N, N, N, 16});
  test({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}, {3, 9, 20, N, N, 15, 7});
}
