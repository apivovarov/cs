#include <iostream>
#include <vector>
#include <climits>

// 64. Minimum Path Sum
class Solution {
 public:
  int minPathSum(std::vector<std::vector<int>>& grid) {
    int rsz = grid.size();
    if (rsz == 0) return 0;
    int csz = grid[0].size();
    if (csz == 0) return 0;
    if (rsz == 1 && csz == 1) return grid[0][0];

    for (int i = 0; i < rsz; ++i) {
      for (int j = 0; j < csz; ++j) {
        if (i == 0 && j == 0) continue;
        int s1 = INT_MAX;
        int s2 = INT_MAX;
        if (i > 0) s1 = grid[i - 1][j];
        if (j > 0) s2 = grid[i][j - 1];
        int s = s1 < s2 ? s1 : s2;
        grid[i][j] += s;
      }
    }
    return grid[rsz - 1][csz - 1];
  }
};

void test(const std::vector<std::vector<int>>& _grid, int expected) {
  Solution sol;
  std::vector<std::vector<int>> grid = _grid;
  int res = sol.minPathSum(grid);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}, 7);
  test({{1, 2, 3}, {4, 5, 6}}, 12);
}
