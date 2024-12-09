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
    if (k == 0) return;
    if (nums.size() < 2) return;
    reverse(nums, 0, nums.size() - k);
    reverse(nums, nums.size() - k, nums.size());
    reverse(nums, 0, nums.size());
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