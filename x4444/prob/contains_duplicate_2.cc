#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
 public:
  bool containsNearbyDuplicate(const std::vector<int>& nums, int k) {
    if (nums.size() < 2 || k < 1) return false;
    std::unordered_set<int> window(k + 1);
    window.insert(nums[0]);
    for (int i = 1; i < nums.size(); ++i) {
      if (!window.insert(nums[i]).second) return true;
      if (window.size() >= k + 1) {
        window.erase(nums[i - k]);
      }
    }
    return false;
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void test(const std::vector<int>& nums, int k, bool expected) {
  Solution sol;
  bool res = sol.containsNearbyDuplicate(nums, k);
  if (res != expected) {
    std::cerr << "ERROR: for " << nums << std::endl;
  }
}

int main() {
  test({1}, 3, false);
  test({1, 2, 1}, 0, false);
  test({1, 2, 3, 1}, 1, false);
  test({1, 2, 3, 1}, 3, true);
  test({1, 2, 4, 3, 1}, 3, false);
  test({1, 2, 4, 3, 1, 2, 3, 1}, 3, true);
  test({5, 1, 2, 4, 3, 1, 6, 7, 1, 5}, 3, true);
  test({1, 1}, 1, true);
  test({1, 2, 1}, 1, false);
}
