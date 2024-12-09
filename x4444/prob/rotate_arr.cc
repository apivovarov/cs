#include <vector>
#include <iostream>

class Solution {
 public:
  void reverse(std::vector<int>& nums, int b, int e) {
    while (b < e) {
      std::swap(nums[b++], nums[--e]);
    }
  }

  void rotate(std::vector<int>& nums, int k) {
    int sz = nums.size();
    if (sz < 2) return;
    k %= sz;
    if (k == 0) return;
    reverse(nums, 0, sz - k);
    reverse(nums, sz - k, sz);
    reverse(nums, 0, sz);
  }
};

int main() {
  Solution sol;
  std::vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  sol.rotate(vec, 3);
  for (const auto& v : vec) std::cout << v << ",";
  std::cout << std::endl;

  vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  sol.rotate(vec, 3);
  for (const auto& v : vec) std::cout << v << ",";
  std::cout << std::endl;
}