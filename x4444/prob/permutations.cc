#include <iostream>
#include <vector>
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
    _next(nums, id + 1, all);
    for (int i = id + 1; i < nums.size(); ++i) {
      tmp = nums[i];
      nums[i] = nums[id];
      nums[id] = tmp;
      _next(nums, id + 1, all);
      nums[id] = nums[i];
      nums[i] = tmp;
    }
  }

 public:
  std::vector<std::vector<int>> permute(const std::vector<int>& _nums) {
    int sz = _nums.size();
    if (sz == 0) return {};
    if (sz == 1) return {_nums};
    std::vector<std::vector<int>> all;
    std::vector<int> nums = _nums;
    _next(nums, 0, all);
    return all;
  }
};

class Solution2 {
 protected:
  void _next(int id, std::vector<int>& res, std::vector<bool>& used,
             const std::vector<int>& nums,
             std::vector<std::vector<int>>& all_res) {
    if (id >= nums.size()) {
      all_res.push_back(res);
      return;
    }
    for (int i = 0; i < nums.size(); ++i) {
      if (used[i]) continue;
      res[id] = nums[i];
      used[i] = true;
      _next(id + 1, res, used, nums, all_res);
      used[i] = false;
    }
  }

 public:
  std::vector<std::vector<int>> permute(const std::vector<int>& nums) {
    int sz = nums.size();
    if (sz == 0) return {};
    if (sz == 1) return {nums};
    std::vector<std::vector<int>> all_res;

    std::vector<int> res(nums.size());
    std::vector<bool> used(nums.size());
    _next(0, res, used, nums, all_res);
    return all_res;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  auto res = sol.permute(nums);
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
  // test({}, 0);
  // test({42}, 1);
  // test({1, 2}, 2);
  // test({1, 3, 1}, 6);
  test({2, 2, 1, 2}, 24);
  // test({1, 2, 3, 4, 5}, 120);
}
