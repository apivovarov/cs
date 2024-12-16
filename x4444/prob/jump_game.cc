#include <iostream>
#include <vector>

/**
* == Jump Game ==
*
* You are given an integer array nums.
* You are initially positioned at the array's first index, and each element
* in the array represents your maximum jump length at that position.
*
* Return: true if you can reach the last index, or false otherwise.
*/
class Solution {
 protected:
 public:
  bool canJump(const std::vector<int>& nums) {
    if (nums.empty()) return false;
    if (nums.size() == 1) return true;
    if (nums.size() == 2) return nums[0] > 0;

    int maxN = 0;
    for (int i = 0; i <= maxN; ++i) {
      if (i + nums[i] > maxN) {
        maxN = i + nums[i];
      }
      if (maxN >= nums.size() - 1) return true;
    }
    return false;
  }
};

void test(const std::vector<int>& nums, bool expected) {
  Solution sol;
  bool res = sol.canJump(nums);
  if (res != expected) {
    std::cerr << std::boolalpha << "ERROR: exp: " << expected << std::endl;
  }
}

int main() {
  test({}, false);
  test({1}, true);
  test({1, 1}, true);
  test({0, 1}, false);
  test({2, 3, 1, 1, 4}, true);
  test({3, 2, 1, 0, 4}, false);
}
