#include <iostream>
#include <vector>

class Solution {
 public:
  void setZeroes(std::vector<std::vector<int>>& matrix) {
    int nRows = matrix.size();
    if (nRows == 0) return;
    int nCols = matrix[0].size();
    if (nCols == 0) return;

    std::vector<bool> rowToZero(nRows);
    std::vector<bool> colToZero(nCols);

    for (int j = 0; j < nRows; ++j) {
      for (int i = 0; i < nCols; ++i) {
        if (matrix[j][i] == 0) {
          rowToZero[j] = true;
          colToZero[i] = true;
        }
      }
    }

    for (int j = 0; j < nRows; ++j) {
      for (int i = 0; i < nCols; ++i) {
        if (rowToZero[j] || colToZero[i]) matrix[j][i] = 0;
      }
    }
  }
};

void test(const std::vector<std::vector<int>>& matrix,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = matrix;
  sol.setZeroes(res);
  if (res != expected) {
    std::cerr << "ERROR: " << std::endl;
  }
}

int main() {
  test({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}});
  test({{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}},
       {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}});
}
