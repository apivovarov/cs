#include <iostream>
#include <iomanip>
#include <vector>

// 188. Best Time to Buy and Sell Stock IV
class Solution {
 public:
  int maxProfit(int k, std::vector<int>& prices) {
    int sz = prices.size();
    if (sz == 0 || k == 0) return 0;
    if (sz == 1) return 0;
    if (sz == 2) return std::max(0, prices[1] - prices[0]);

    if (k >= sz / 2) {
      // unlimited case - accum all ups
      int sum = 0;
      for (int i = 1; i < sz; ++i) {
        if (prices[i] - prices[i - 1] > 0) {
          sum += prices[i] - prices[i - 1];
        }
      }
      return sum;
    }

    std::vector<std::vector<int>> dp(k + 1, std::vector<int>(sz));
    for (int i = 1; i <= k; ++i) {
      int maxDiff = 0 - prices[0];
      for (int j = 1; j < sz; ++j) {
        dp[i][j] = std::max(dp[i][j - 1], prices[j] + maxDiff);
        maxDiff = std::max(maxDiff, dp[i - 1][j] - prices[j]);
      }
    }

    // DP
    std::cerr << "====================================" << std::endl;
    for (int i = 0; i <= k; ++i) {
      for (int j = 0; j < sz; ++j) {
        std::cerr << std::setw(5) << dp[i][j] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << "====================================" << std::endl;

    return dp[k][sz - 1];
  }
};

void test(int k, std::vector<int> vec, int expected) {
  Solution sol;
  int res = sol.maxProfit(k, vec);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  // unlim
  test(100, {30, 29, 28}, 0);
  test(100, {28, 29, 30}, 2);
  test(100, {30, 29, 28, 28, 29, 32, 35, 36}, 8);
  test(100,
       {30, 29, 28, 28, 29, 32, 35, 36, 35, 34, 33, 33, 34, 43, 50, 47, 35, 37},
       8 + 17 + 2);

  // k=2
  test(2, {3, 3, 5, 0, 0, 3, 1, 4}, 6);
  test(2, {9, 8, 7, 6, 4, 3, 1}, 0);
  test(2, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 8);
  test(1, {1}, 0);
  test(1, {1, 2}, 1);

  test(2, {3, 2, 6, 5, 0, 3}, 7);
  test(2, {2, 4, 1}, 2);

  test(2, {20, 21, 22, 23, 23, 23, 14, 14, 15, 15, 16,
           16, 7,  7,  8,  9,  10, 11, 12, 1,  1,  1},
       8);
  test(3, {20, 21, 22, 23, 23, 23, 14, 14, 15, 15, 16,
           16, 7,  7,  8,  9,  10, 11, 12, 1,  1,  1},
       10);
  test(1, {20, 21, 22, 23, 23, 23, 14, 14, 15, 15, 16,
           16, 7,  7,  8,  9,  10, 11, 12, 1,  1,  1},
       5);
  test(100, {20, 21, 22, 23, 23, 23, 14, 14, 15, 15, 16,
             16, 7,  7,  8,  9,  10, 11, 12, 1,  1,  1},
       10);
}
