#include <iostream>
#include <vector>

class Solution {
 public:
  int minSubArrayLen(int target, const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0] >= target ? 1 : 0;
    if (nums[0] >= target) return 1;

    int b = 0;
    int sum = nums[0];
    int minSz = nums.size();

    for (int i = 1; i < nums.size(); ++i) {
      sum += nums[i];
      while (sum - nums[b] >= target) {
        sum -= nums[b];
        ++b;
      }
      if (sum >= target) {
        int _sz = i - b + 1;
        if (_sz == 1) return 1;
        if (_sz < minSz) minSz = _sz;
      }
    }
    if (sum < target) return 0;
    return minSz;
  }
};

void test(int target, const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.minSubArrayLen(target, nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test(1, {}, 0);
  test(10, {11}, 1);
  test(10, {9}, 0);
  test(10, {4, 6}, 2);
  test(10, {4, 6, 1}, 2);
  test(10, {4, 6, 11, 1}, 1);

  test(7, {2, 3, 1, 2, 4, 3}, 2);
  test(4, {1, 4, 4}, 1);
  test(11, {1, 1, 1, 1, 1, 1, 1, 1}, 0);
  test(11, {1, 2, 3, 4, 5}, 3);
  test(213, {12, 28, 83, 4, 25, 26, 25, 2, 25, 25, 25, 12}, 8);
  test(80, {10, 5, 13, 4, 8, 4, 5, 11, 14, 9, 16, 10, 20, 8}, 6);
}
