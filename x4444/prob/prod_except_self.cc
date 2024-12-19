#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    if (nums.empty()) return {};
    if (nums.size() == 1) return nums;
    if (nums.size() == 2) return {nums[1], nums[0]};

    int prod = 1;
    int zero_id = -1;
    int zero_cnt = 0;
    std::vector<int> res(nums.size());
    res[0] = 1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        ++zero_cnt;
        zero_id = i;
      } else {
        prod *= nums[i];
      }
      if (i == 0) {
        continue;
      }
      if (nums[i - 1] == 0) {
        res[i] = res[i - 1];
      } else {
        res[i] = res[i - 1] * nums[i - 1];
      }
    }

    if (zero_cnt > 1) {
      std::vector<int> res(nums.size());
      return res;
    }
    if (zero_cnt == 1) {
      std::vector<int> res(nums.size());
      res[zero_id] = prod;
      return res;
    }

    prod = 1;

    for (int i = nums.size() - 2; i >= 0; --i) {
      prod *= nums[i + 1];
      res[i] *= prod;
    }

    return res;
  }
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& nums) {
  for (int v : nums) {
    os << v << ",";
  }
  return os;
}

void test(const std::vector<int>& nums, const std::vector<int>& exp) {
  Solution sol;
  std::vector<int> res = sol.productExceptSelf(nums);

  if (res != exp) {
    std::cerr << "ERROR: res: " << res << ", exp: " << exp << std::endl;
  }
}

int main() {
  test({}, {});
  test({0}, {0});
  test({0, 1}, {1, 0});
  test({1, 2, 3, 4}, {24, 12, 8, 6});
  test({-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0});
  test({-1, 1, 0, -3, 0, 3}, {0, 0, 0, 0, 0, 0});
}
