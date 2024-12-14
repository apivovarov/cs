#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

class Solution {
 protected:
  void _next(std::vector<int>& nums, int id,
             std::vector<std::vector<int>>& all) {
    int tmp;
    if (id == nums.size()) {
      all.push_back(nums);
      return;
    }
    std::array<int, 21> visited = {};
    visited[nums[id] + 10] = 1;
    _next(nums, id + 1, all);
    for (int i = id + 1; i < nums.size(); ++i) {
      if (visited[nums[i] + 10]) continue;
      visited[nums[i] + 10] = 1;
      tmp = nums[i];
      nums[i] = nums[id];
      nums[id] = tmp;
      _next(nums, id + 1, all);
      nums[id] = nums[i];
      nums[i] = tmp;
    }
  }

 public:
  std::vector<std::vector<int>> permuteUnique(const std::vector<int>& _nums) {
    int sz = _nums.size();
    if (sz == 0) return {};
    if (sz == 1) return {_nums};
    std::vector<std::vector<int>> all;
    std::vector<int> nums = _nums;
    _next(nums, 0, all);
    return all;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  auto res = sol.permuteUnique(nums);
  for (const auto& vec : res) {
    for (const auto& v : vec) {
      std::cerr << v << ",";
    }
    std::cerr << std::endl;
  }

  int in_sz = nums.size();
  bool sz_res = std::all_of(
      res.begin(), res.end(),
      [in_sz](const std::vector<int>& vec) { return vec.size() == in_sz; });
  if (!sz_res) std::cerr << "ERROR: bad elem size" << std::endl;
  if (res.size() != expected) {
    std::cerr << "ERROR: size: " << res.size() << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({42}, 1);
  test({1, 1}, 1);
  test({1, 2}, 2);
  test({1, 3, 1}, 3);
  test({2, 2, 1, 2}, 4);
  test({1, 2, 2, 1}, 6);
  test({1, 2, 1, 1, 2}, 10);
}
