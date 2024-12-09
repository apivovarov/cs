#include <vector>
#include <iostream>
#include <stdexcept>

class Solution {
 public:
  int removeElement(std::vector<int>& nums, int val) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0] == val ? 0 : 1;
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
      if (nums[low] == val) {
        if (nums[high] != val) nums[low] = nums[high];
        --high;
      } else {
        ++low;
      }
    }
    return high + 1;
  }
};

class Solution2 {
 public:
  int removeElement(std::vector<int>& nums, int val) {
    if (nums.empty()) return 0;
    int low = 0;
    int high = nums.size() - 1;

    // find next non-val id moving from back
    while (high >= 0 && nums[high] == val) {
      --high;
    }
    if (high <= 0) return high + 1;

    while (low < high) {
      if (nums[low] == val) {
        // swap
        nums[low] = nums[high];
        // find next non-val id moving from back
        --high;
        while (high > low && nums[high] == val) {
          --high;
        }
      }
      ++low;
    }
    return high + 1;
  }
};

void test(std::vector<int> vec, int expected) {
  Solution sol;
  int sz = sol.removeElement(vec, 3);
  std::cerr << "size: " << sz << std::endl;
  if (sz != expected) throw std::runtime_error("size is wrong");
  for (int i = 0; i < sz; ++i) {
    std::cerr << vec[i] << ",";
  }
  std::cerr << std::endl;
}

int main() {
  test({}, 0);
  test({3}, 0);
  test({3, 3}, 0);
  test({2}, 1);

  test({2, 2}, 2);
  test({3, 2}, 1);
  test({2, 3}, 1);
  test({3, 2, 3}, 1);
  test({2, 3, 2}, 2);
  test({3, 3, 2, 3}, 1);
  test({3, 2, 2, 3}, 2);
  test({3, 2, 3, 3}, 1);
}