#include <iostream>
#include <vector>

// 136. Single Number
class Solution {
 public:
  int singleNumber(const std::vector<int>& nums) {
    int acc = 0;
    for (int v : nums) {
      acc ^= v;
    }
    return acc;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.singleNumber(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({2, 2, 1}, 1);
  test({4, 1, 2, 1, 2}, 4);
  test({1}, 1);
  test({4}, 4);
  test({44, 4, 44}, 4);
}
