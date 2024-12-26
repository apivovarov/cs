#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    if (nums.size() < 3) return {};
    if (nums.size() == 3)
      return nums[0] + nums[1] + nums[2] == 0
                 ? std::vector<std::vector<int>>{nums}
                 : std::vector<std::vector<int>>{};
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    for (int i = 0; i < nums.size() - 2; ++i) {
      if (nums[i] > 0) break;
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      int b = i + 1;
      int e = nums.size() - 1;
      while (b < e) {
        if (nums[b] > -nums[i]) break;
        int sum = nums[b] + nums[e];
        if (sum == -nums[i]) {
          res.push_back({nums[i], nums[b], nums[e]});
          while (b < e && nums[b] == nums[b + 1]) ++b;
          while (b < e && nums[e] == nums[e - 1]) --e;
          ++b;
          --e;
        } else if (sum < -nums[i]) {
          ++b;
        } else {
          --e;
        }
      }
    }
    return res;
  }
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vv) {
  os << '[';
  for (int v : vv) os << v << ",";
  os << ']';
  return os;
}

void test(const std::vector<int>& _nums,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<int> nums = _nums;
  std::vector<std::vector<int>> res = sol.threeSum(nums);
  if (res != expected) {
    std::cerr << "Error: " << std::endl;
    for (const std::vector<int>& vv : res) {
      std::cerr << vv << ",";
    }
    std::cerr << std::endl;
  }
}

int main() {
  test({-1, 0, 1, 2, -1, -4}, {{-1, -1, 2}, {-1, 0, 1}});
  test({-12, -9, -14, -15, 4, 7, 23}, {{-14, -9, 23}});
}
