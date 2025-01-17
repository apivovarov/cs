#include <iostream>
#include <vector>

// 198. House Robber
class Solution {
 public:
  int rob(const std::vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    if (nums.size() == 2) return std::max(nums[0], nums[1]);
    if (nums.size() == 3) return std::max(nums[0] + nums[2], nums[1]);

    int prpr_max = nums[0];
    int prev = nums[1];
    int _max = std::max(nums[0], nums[1]);

    for (int i = 2; i < nums.size(); ++i) {
      int curr = prpr_max + nums[i];
      if (prev > prpr_max) prpr_max = prev;
      _max = std::max(curr, _max);
      prev = curr;
    }
    return _max;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.rob(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1, 2, 3, 1}, 4);
  test({2, 7, 9, 3, 1}, 12);
  test({2, 7, 1, 1, 9, 3, 1}, 17);
}
