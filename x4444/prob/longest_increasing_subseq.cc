#include <iostream>
#include <vector>

// 300. Longest Increasing Subsequence
class Solution {
 public:
  int lengthOfLIS(const std::vector<int>& nums) {
    std::vector<int> dp(nums.size(), 1);
    int gMax = 1;
    for (int i = 1; i < nums.size(); ++i) {
      int max = 0;
      for (int j = 0; j < i; ++j) {
        if (nums[j] >= nums[i]) continue;
        if (dp[j] > max) max = dp[j];
      }
      ++max;
      dp[i] = max;
      if (max > gMax) gMax = max;
    }
    return gMax;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.lengthOfLIS(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({10, 9, 2, 5, 3, 7, 101, 18}, 4);
  test({0, 1, 0, 3, 2, 3}, 4);
  test({7, 7, 7, 7, 7, 7, 7}, 1);
  test({7}, 1);
}
