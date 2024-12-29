#include <iostream>
#include <vector>

class Solution {
 public:
  void gameOfLife(std::vector<std::vector<int>>& board) {
    int nRows = board.size();
    if (nRows == 0) return;
    int nCols = board[0].size();
    if (nCols == 0) return;
    if (nRows == 1 && nCols == 1) board[0][0] = 0;

    std::vector<std::vector<bool>> mask(nRows, std::vector<bool>(nCols));

    for (int j = 0; j < nRows; ++j) {
      for (int i = 0; i < nCols; ++i) {
        int nAl = 0;
        for (int jj = -1; jj < 2; ++jj) {
          if (j + jj < 0 || j + jj >= nRows) continue;
          for (int ii = -1; ii < 2; ++ii) {
            if (jj == 0 && ii == 0) continue;
            if (i + ii < 0 || i + ii >= nCols) continue;
            nAl += board[j + jj][i + ii];
          }
        }
        if (board[j][i] == 1) {
          if (nAl < 2 || nAl > 3) mask[j][i] = true;
        } else if (nAl == 3) {
          mask[j][i] = true;
        }
      }
    }
    for (int j = 0; j < nRows; ++j) {
      for (int i = 0; i < nCols; ++i) {
        board[j][i] ^= mask[j][i];
      }
    }
  }
};

void test(const std::vector<std::vector<int>>& board,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = board;
  sol.gameOfLife(res);
  if (res != expected) {
    std::cerr << "Error: " << std::endl;
  }
}

int main() {
  test({{1}}, {{0}});
  test({{0, 1}}, {{0, 0}});
  test({{0}, {1}}, {{0}, {0}});
  test({{1, 1}}, {{0, 0}});
  test({{1}, {1}}, {{0}, {0}});
  test({{1, 1}, {1, 1}}, {{1, 1}, {1, 1}});
  test({{1, 1}, {1, 0}}, {{1, 1}, {1, 1}});
  test({{0, 0}, {1, 1}}, {{0, 0}, {0, 0}});
  test({{1, 0}, {1, 0}}, {{0, 0}, {0, 0}});
  test({{1, 1, 1}, {0, 1, 0}, {1, 1, 1}}, {{1, 1, 1}, {0, 0, 0}, {1, 1, 1}});
  test({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}}, {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});
  test({{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}, {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}});
  test({{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}, {{1, 1, 0}, {1, 0, 1}, {0, 1, 0}});
}
