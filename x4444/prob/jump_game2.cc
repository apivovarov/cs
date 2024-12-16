#include <iostream>
#include <vector>

class Solution {
 public:
  int jump(const std::vector<int>& nums) {
    int sz = nums.size();
    if (sz < 2) return 0;
    if (nums[0] >= sz - 1) return 1;
    int jumps = 1;
    int fa = nums[0];
    int e = nums[0];
    for (int i = 1; i < sz - 1; ++i) {
      int fa0 = i + nums[i];
      if (fa0 > fa) fa = fa0;
      if (fa >= sz - 1) return jumps + 1;
      if (e == i) {
        ++jumps;
        e = fa;
      }
    }
    return -1;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.jump(nums);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({1}, 0);
  test({1, 1}, 1);
  test({3, 2, 1}, 1);
  test({1, 1, 1}, 2);
  test({1, 5, 1, 1, 1}, 2);
  test({1, 1, 1, 1}, 3);
  test({1, 2, 1, 1}, 2);
  test({1, 2, 1, 2, 1, 1}, 3);
}
