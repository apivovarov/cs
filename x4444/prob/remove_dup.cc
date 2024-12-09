#include <vector>
#include <iostream>

class Solution {
 public:
  int removeDuplicates(std::vector<int>& nums) {
    if (nums.size() < 2) return nums.size();
    if (nums.size() == 2) return nums[0] == nums[1] ? 1 : 2;

    int pn = 1;
    int pp = 0;
    while (pn < nums.size()) {
      if (nums[pn] > nums[pp]) {
        ++pp;
        nums[pp] = nums[pn];
      }
      ++pn;
    }
    return pp + 1;
  }
};

void test(std::vector<int> vec, int expected) {
  Solution sol;
  int sz = sol.removeDuplicates(vec);
  std::cerr << "size: " << sz << std::endl;
  if (sz != expected) throw std::runtime_error("Wrong size");
  for (const auto& v : vec) {
    std::cerr << v << ",";
  }
  std::cerr << std::endl;
}

int main() {
  test({}, 0);
  test({5}, 1);
  test({5, 5}, 1);
  test({4, 5}, 2);
  test({1, 1, 1, 2, 2, 2, 3, 4, 4}, 4);
  test({1, 2, 3, 4}, 4);
  test({1, 2, 3, 3, 4}, 4);
  test({1, 2, 3, 4, 4}, 4);
}