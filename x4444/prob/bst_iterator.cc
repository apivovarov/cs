#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class BSTIterator {
  std::vector<TreeNode*> st;
  TreeNode dummy;
  TreeNode* currN = nullptr;
  int leftCnt = 1;  // account for dummy node - most left node

 public:
  void goLeft() {
    while (currN->left) {
      st.push_back(currN);
      currN = currN->left;
      ++leftCnt;
    }
  }

  BSTIterator(TreeNode* root) {
    if (!root) {
      currN = &dummy;
      return;
    }

    currN = root;
    goLeft();
    st.push_back(currN);
    currN = &dummy;
  }

  int next() {
    // go right
    if (currN->right) {
      st.push_back(currN);
      currN = currN->right;
      goLeft();
    } else {
      // go up
      TreeNode* par = st.back();
      st.pop_back();
      while (currN == par->right) {
        currN = par;
        par = st.back();
        st.pop_back();
      }
      --leftCnt;
      currN = par;
    }
    return currN->val;
  }

  bool hasNext() { return leftCnt > 0 || currN->right; }
};

#include <limits>
constexpr int N = std::numeric_limits<int>::min();

void delTree(TreeNode* n) {
  if (!n) return;
  delTree(n->left);
  delTree(n->right);
  delete (n);
}

bool isSame(TreeNode* p, TreeNode* q) {
  if (p == nullptr && q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;
  if (p->val != q->val) return false;
  if (!isSame(p->left, q->left)) return false;
  if (!isSame(p->right, q->right)) return false;
  return true;
}

TreeNode* makeTree(const std::vector<int>& vv) {
  if (vv.empty()) return nullptr;
  std::vector<TreeNode*> nv;
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

int main() {
  TreeNode* root = makeTree({10, 5, 15, N, 6, N, N, N, N, N, 7, N, N, N, N});
  BSTIterator it(root);
  for (int i = 0; i < 5; ++i) {
    std::cerr << "hasNext pre: " << std::boolalpha << it.hasNext() << std::endl;
    std::cerr << "next: " << it.next() << std::endl;
    std::cerr << "hasNext post: " << std::boolalpha << it.hasNext()
              << std::endl;
  }
  std::cerr << std::endl;
}
