#include <iostream>
#include <vector>

// 63. Unique Paths II
class Solution {
 public:
  int uniquePathsWithObstacles(
      const std::vector<std::vector<int>>& obstacleGrid) {
    int rsz = obstacleGrid.size();
    if (rsz == 0) return 0;
    int csz = obstacleGrid[0].size();
    if (csz == 0) return 0;
    if (obstacleGrid[0][0] || obstacleGrid[rsz - 1][csz - 1]) return 0;
    if (rsz == 1 && csz == 1) {
      return 1;
    }

    std::vector<int> dp(csz, 0);
    dp[0] = 1;

    for (int i = 0; i < rsz; ++i) {
      for (int j = 0; j < csz; ++j) {
        // set 0 in dp cell if obstacle
        if (obstacleGrid[i][j]) {
          dp[j] = 0;
          continue;
        }
        if (j > 0) {
          dp[j] += dp[j - 1];
        }
      }
    }
    return dp[csz - 1];
  }
};

void test(const std::vector<std::vector<int>>& obstacleGrid, int expected) {
  Solution sol;
  int res = sol.uniquePathsWithObstacles(obstacleGrid);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, 2);
  test({{0, 0, 0}, {1, 1, 0}, {0, 0, 0}}, 1);
  test({{0, 1}, {0, 0}}, 1);
  test({{1, 0}}, 0);
  test({{0, 0, 1}}, 0);
  test({{0}}, 1);
}
