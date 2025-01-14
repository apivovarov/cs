#include <iostream>
#include <vector>

// 74. Search a 2D Matrix
class Solution {
 public:
  bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int rsz = matrix.size();
    int csz = matrix[0].size();
    if (target < matrix[0][0] || target > matrix[rsz - 1][csz - 1])
      return false;
    if (target == matrix[0][0] || target == matrix[rsz - 1][csz - 1])
      return true;
    int b = 0;
    int e = rsz * csz;
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      int v = matrix[m / csz][m % csz];
      if (v == target)
        return true;
      else if (v < target)
        b = m + 1;
      else
        e = m;
    }
    return false;
  }
};

void test(const std::vector<std::vector<int>>& matrix, int target,
          bool expected) {
  Solution sol;
  bool res = sol.searchMatrix(matrix, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << " , exp: " << expected << std::endl;
  }
}

int main() {
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3, true);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 13, false);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 1, true);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 60, true);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 61, false);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 0, false);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 22, false);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 34, true);
  test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 35, false);
}
