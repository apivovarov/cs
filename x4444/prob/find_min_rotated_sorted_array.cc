#include <iostream>
#include <vector>

// 153. Find Minimum in Rotated Sorted Array
class Solution {
 public:
  int findMin(const std::vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    int b = 0;
    int e = nums.size();
    // Check if array not rotated and the first elem is min.
    if (nums[0] < nums[e - 1]) return nums[0];
    // Check if the last elem is min - needed to simplify binary search below
    if (nums[e - 1] < nums[e - 2]) return nums[e - 1];
    int m = 0;
    // If range size is less than 3 - do not do binary search.
    while (e - b > 2) {
      m = b + (e - b) / 2;
      // std::cerr << b << "," << m << "," << e << std::endl;
      if (nums[m] > nums[m + 1]) return nums[m + 1];
      if (nums[m] < nums[m - 1]) return nums[m];

      if (nums[m] >= nums[b]) {
        // peak on right
        b = m + 1;
      } else {
        e = m;
      }
    }
    // Should never reach here for a valid rotated array
    return nums[b] < nums[e - 1] ? nums[b] : nums[e - 1];
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.findMin(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test({1}, 1);
  test({1, 2}, 1);
  test({2, 1}, 1);
  test({1, 2, 3}, 1);
  test({3, 1, 2}, 1);
  test({2, 3, 1}, 1);

  test({1, 2, 3, 4}, 1);
  test({2, 3, 4, 1}, 1);
  test({3, 4, 1, 2}, 1);
  test({2, 3, 4, 1}, 1);
}
