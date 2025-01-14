#include <iostream>
#include <vector>

// 162. Find Peak Element
// Go to middle, check for /\ case. if not for to L\ or R/
class Solution {
 public:
  int findPeakElement(const std::vector<int>& nums) {
    if (nums.size() == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums.back() > nums[nums.size() - 2]) return nums.size() - 1;
    int b = 0;
    int e = nums.size();
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      // std::cerr << b << "," << m << "," << e << std::endl;
      if (nums[m] > nums[m - 1] && nums[m] > nums[m + 1]) return m;
      if (nums[m - 1] > nums[m]) {
        e = m;
      } else {
        b = m + 1;
      }
    }
    // std::cerr << "fin: " << b << "," << m << "," << e << std::endl;
    return b;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.findPeakElement(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1}, 0);

  test({1, 2}, 1);
  test({2, 1}, 0);
  test({3, 2, 1}, 0);
  test({1, 2, 3}, 2);
  test({1, 2, 3, 1}, 2);
  test({1, 2, 1, 3, 5, 6, 4}, 5);
  test({16, 10, 6, 3, 2}, 0);
  test({15, 16, 10, 6, 3, 2}, 1);
  test({1, 2, 1, 3, 5, 7, 16}, 6);
  test({1, 2, 1, 3, 5, 7, 16, 15}, 6);
  test({1, 2, 1, 3, 5, 7, 16, 1, 0, -4}, 6);

  test({1, 2, 1, 2, 1}, 1);
}
