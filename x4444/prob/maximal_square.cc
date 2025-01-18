#include <iostream>
#include <vector>

// 221. Maximal Square
class Solution {
 public:
  int maximalSquare(const std::vector<std::vector<char>>& matrix) {
    int rsz = matrix.size();
    if (rsz == 0) return 0;
    int csz = matrix[0].size();
    if (csz == 0) return 0;

    std::vector<std::vector<int>> dp(rsz, std::vector<int>(csz, 0));

    int max = 0;
    for (int i = 0; i < rsz; ++i) {
      for (int j = 0; j < csz; ++j) {
        if (matrix[i][j] == '0') {
          dp[i][j] = 0;
          continue;
        }
        int D = 0;
        int U = 0;
        int L = 0;
        if (i > 0 && j > 0) D = dp[i - 1][j - 1];
        if (i > 0) U = dp[i - 1][j];
        if (j > 0) L = dp[i][j - 1];
        int x = std::min(std::min(D, U), L);
        ++x;
        dp[i][j] = x;
        if (x > max) max = x;
      }
    }
    return max * max;
  }
};

void test(const std::vector<std::vector<char>>& matrix, int expected) {
  Solution sol;
  int res = sol.maximalSquare(matrix);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}},
       4);
  test({{'0', '1'}, {'1', '0'}}, 1);
  test({{'0'}}, 0);
}
