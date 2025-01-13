#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

// Definition for a QuadTree node.
class Node {
 public:
  bool val;
  bool isLeaf;
  Node* topLeft;
  Node* topRight;
  Node* bottomLeft;
  Node* bottomRight;

  Node() {
    val = false;
    isLeaf = false;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
       Node* _bottomLeft, Node* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

// 427. Construct Quad Tree
class Solution {
 public:
  bool allSame(int T, int B, int L, int R,
               const std::vector<std::vector<int>>& grid) {
    int v = grid[T][L];
    for (int r = T; r < B; ++r) {
      for (int c = L; c < R; ++c) {
        if (grid[r][c] != v) return false;
      }
    }
    return true;
  }

  Node* getRoot(int T, int B, int L, int R,
                const std::vector<std::vector<int>>& grid) {
    if (B - T == 1) return new Node(grid[T][L], true);
    if (T >= B) return nullptr;

    if (allSame(T, B, L, R, grid)) {
      return new Node(grid[T][L], true);
    }
    int Mr = T + (B - T) / 2;
    int Mc = L + (R - L) / 2;
    return new Node(0, false, getRoot(T, Mr, L, Mc, grid),
                    getRoot(T, Mr, Mc, R, grid), getRoot(Mr, B, L, Mc, grid),
                    getRoot(Mr, B, Mc, R, grid));
  }

  Node* construct(const std::vector<std::vector<int>>& grid) {
    int N = grid.size();
    if (N == 0) return nullptr;
    if (N == 1) return new Node(grid[0][0], true);
    return getRoot(0, N, 0, N, grid);
  }
};

void test(const std::vector<std::vector<int>>& grid,
          const std::string& expected) {
  Solution sol;
  Node* n = sol.construct(grid);

  std::queue<Node*> qu;
  qu.push(n);

  std::ostringstream ss;
  ss << "{";
  while (!qu.empty()) {
    int sz = qu.size();
    bool allLeaf = true;
    for (int i = 0; i < sz; ++i) {
      Node* n = qu.front();
      qu.pop();
      if (n) {
        ss << "{" << n->isLeaf << "," << n->val << "},";
        allLeaf &= n->isLeaf;
        qu.push(n->topLeft);
        qu.push(n->topRight);
        qu.push(n->bottomLeft);
        qu.push(n->bottomRight);
      } else {
        ss << "N,";
        qu.push(nullptr);
        qu.push(nullptr);
        qu.push(nullptr);
        qu.push(nullptr);
      }
    }
    if (allLeaf) break;
  }
  std::string res = ss.str();
  res.pop_back();
  res.push_back('}');

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test({{1}}, "{{1,1}}");
  test({{0}}, "{{1,0}}");
  test({{0, 1}, {1, 0}}, "{{0,0},{1,0},{1,1},{1,1},{1,0}}");
  test({{1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0}},
       "{{0,0},{1,1},{0,0},{1,1},{1,0},N,N,N,N,{1,0},{1,0},{1,1},{1,1},N,N,N,N,"
       "N,N,N,N}");
}
