#include <iostream>
#include <vector>

// 35. Search Insert Position
class Solution {
 public:
  int searchInsert(const std::vector<int>& nums, int target) {
    if (nums.empty() || target < nums[0]) return 0;
    if (nums.size() == 1) return target > nums[0];
    if (target > nums.back()) return nums.size();
    int b = 0;
    int e = nums.size();
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      // std::cerr << b << " " << m  << " " << e << std::endl;
      if (nums[m] == target) {
        return m;
      } else if (nums[m] < target) {
        b = m + 1;
      } else {
        e = m;
      }
    }
    // std::cerr << b << " " << m << " " << e << std::endl;
    return b;
  }
};

void test(const std::vector<int>& nums, int target, int expected) {
  Solution sol;
  int res = sol.searchInsert(nums, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << " , exp: " << expected << std::endl;
  }
}

int main() {
  test({}, 5, 0);
  test({4}, 5, 1);
  test({4}, 3, 0);
  test({1, 3, 5, 6}, 0, 0);
  test({1, 3, 5, 6}, -10, 0);
  test({1, 3, 5, 6}, 60, 4);
  test({1, 3, 5, 6}, 5, 2);
  test({1, 3, 5, 6}, 2, 1);
  test({1, 3, 5, 6}, 7, 4);
  test({1, 3, 5, 8}, 6, 3);
  test({1, 3, 5, 8, 12}, 13, 5);
  test({1, 3, 5, 8, 12}, 12, 4);
  test({1, 3, 5, 8, 12}, 11, 4);
  test({1, 3, 5, 8, 12}, 7, 3);
  test({1, 3, 5, 8, 12}, 5, 2);
  test({1, 3, 5, 8, 12}, 4, 2);
  test({1, 3, 5, 8, 12}, 3, 1);
  test({1, 3, 5, 8, 12}, 2, 1);
  test({1, 3, 5, 8, 12}, 1, 0);
  test({1, 3, 5, 8, 12}, -1, 0);
}
