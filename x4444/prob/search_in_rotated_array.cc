#include <iostream>
#include <vector>

// 33. Search in Rotated Sorted Array
class Solution {
 public:
  int findPeakElement(const std::vector<int>& nums) {
    int b = 0;
    int e = nums.size();
    if (nums[0] > nums[1] && nums[0] > nums[e - 1]) return 0;
    if (nums[e - 1] > nums[e - 2] && nums[e - 1] > nums[0]) return e - 1;
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      if (nums[m] > nums[m - 1] && nums[m] > nums[m + 1]) return m;
      if (nums[m] > nums[0]) {
        // peak on the left
        b = m + 1;
      } else {
        e = m;
      }
    }
    return b;
  }
  int search(const std::vector<int>& nums, int target) {
    int sz = nums.size();
    if (sz == 0) return -1;
    if (nums[0] == target) return 0;
    if (nums[sz - 1] == target) return sz - 1;
    if (sz <= 2) return -1;
    int peakId = findPeakElement(nums);
    // std::cerr << "peakId: " << peakId << std::endl;
    int b = 0;
    int e = sz;
    int m = 0;
    if (target > nums[0]) {
      // search in left of peak
      e = peakId + 1;
    } else {
      // search in right of peak
      b = peakId + 1;
    }

    if (target < nums[b]) return -1;
    if (target > nums[e - 1]) return -1;

    while (b < e) {
      m = b + (e - b) / 2;
      if (nums[m] == target) return m;
      // target on the left
      if (nums[m] > target) {
        e = m;
      } else {
        b = m + 1;
      }
    }
    // not found
    return -1;
  }
};

void test(const std::vector<int>& nums, int target, int expected) {
  Solution sol;
  int res = sol.search(nums, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 1, -1);
  test({1}, 5, -1);
  test({5}, 5, 0);

  test({1, 2}, 1, 0);
  test({1, 2}, 2, 1);
  test({1, 2}, 5, -1);
  test({2, 1}, 1, 1);
  test({2, 1}, 2, 0);
  test({2, 1}, 5, -1);

  test({2, 3, 1}, 1, 2);
  test({2, 3, 1}, 2, 0);
  test({2, 3, 1}, 3, 1);

  test({3, 1, 2}, 1, 1);
  test({3, 1, 2}, 2, 2);
  test({3, 1, 2}, 3, 0);

  test({1, 2, 3}, 1, 0);
  test({1, 2, 3}, 2, 1);
  test({1, 2, 3}, 3, 2);
  test({1, 2, 3}, 4, -1);
  test({1, 2, 3}, -5, -1);

  test({3, 4, 1, 2}, 1, 2);
  test({3, 4, 1, 2}, 2, 3);
  test({3, 4, 1, 2}, 3, 0);
  test({3, 4, 1, 2}, 4, 1);

  test({4, 5, 1, 2, 3}, 1, 2);
  test({4, 5, 1, 2, 3}, 2, 3);
  test({4, 5, 1, 2, 3}, 3, 4);
  test({4, 5, 1, 2, 3}, 4, 0);
  test({4, 5, 1, 2, 3}, 5, 1);
  test({4, 5, 1, 2, 3}, -4, -1);
  test({4, 5, 1, 2, 3}, 6, -1);
  test({40, 50, 10, 20, 30}, 35, -1);
  test({40, 50, 10, 20, 30}, 15, -1);

  //   test({3, 4, 5, 1, 2}, 2);
  test({20, 30, 40, 50, 10}, 10, 4);
  test({20, 30, 40, 50, 10}, 20, 0);
  test({20, 30, 40, 50, 10}, 30, 1);
  test({20, 30, 40, 50, 10}, 40, 2);
  test({20, 30, 40, 50, 10}, 50, 3);
  test({20, 30, 40, 50, 10}, 55, -1);
  test({20, 30, 40, 50, 10}, -50, -1);
  test({20, 30, 40, 50, 10}, 35, -1);
  test({20, 30, 40, 50, 10}, 16, -1);
}
