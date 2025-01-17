#include <iostream>
#include <vector>

// 322. Coin Change
class Solution {
 public:
  int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
      for (int j = 0; j < coins.size(); ++j) {
        int c = coins[j];
        if (c == i) {
          dp[i] = 1;
          break;
        } else if (c > i) {
          continue;
        } else {
          int r = dp[i - c];
          if (r < 0) continue;
          ++r;
          if (dp[i] < 0 || r < dp[i]) dp[i] = r;
        }
      }
    }
    return dp[amount];
  }
};

void test(const std::vector<int>& coins, int amount, int expected) {
  Solution sol;
  int res = sol.coinChange(coins, amount);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1, 2, 5}, 5, 1);
  test({1, 2, 5}, 11, 3);
  test({2}, 3, -1);
  test({1}, 0, 0);
}
