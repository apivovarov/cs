#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>

class Solution {
 public:
  int longestConsecutive(const std::vector<int>& nums) {
    if (nums.size() < 2) return nums.size();
    if (nums.size() == 2) return std::abs(nums[0] - nums[1]) == 1 ? 2 : 1;

    std::unordered_map<int, int> nums_map;
    for (int n : nums) {
      nums_map[n] = 0;
    }
    int maxL = 1;

    for (int n : nums) {
      auto nums_map_it = nums_map.find(n);
      if (nums_map_it->second > 0) continue;
      nums_map_it->second = 1;
      int e = n + 1;
      while (true) {
        auto seq_it = nums_map.find(e);
        if (seq_it == nums_map.end()) {
          --e;
          if (e > n) {
            int L = e - n + 1;
            if (L > maxL) maxL = L;
            nums_map_it->second = L;
          }
          break;
        }

        if (seq_it->second > 1) {
          int L = e - n + seq_it->second;
          if (L > maxL) maxL = L;
          nums_map_it->second = L;
          break;
        }

        // visit
        seq_it->second = 1;
        ++e;
      }
    }
    return maxL;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.longestConsecutive(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({100}, 1);
  test({}, 0);
  test({1, 3}, 1);
  test({2, 1}, 2);
  test({100, 4, 200, 1, 3, 2}, 4);
  test({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, 9);
  test({1, 3, 7, 2, 5, 8, 4, 6, 0, 0}, 9);
  test({1, 3, 7, 2, 5, 100, 90, 8, 4, 6, 0, 0}, 9);
  test({1, 3, 7, 2, 5, 100, 8, 4, 6, 90, 0, 0}, 9);
  test({80, 1, 3, 7, 2, 5, 100, 8, 4, 6, 90, 0, 0}, 9);
  test({80, 1, 3, 7, 2, 5, 100, 8, 4, 6, 90, 0, 0, 40}, 9);
  test({5, 4, 3, 2, 1, 90, 30, 9, 8, 6, 7, 0, 40}, 10);
  test({10, 1, 0, 10}, 2);
  test({10, -1, 0, 10}, 2);
  test({10, -1, 10, 0}, 2);
  test({0, 10, -1, 10, -2}, 3);
  test({10, -1, 10, -2}, 2);
  test({-3, 10, -1, 10, -2}, 3);
  test({-3, 10, -1, 10, -2, 0}, 4);
  test({-3, 1, 10, -1, 10, -2, 0}, 5);
}
