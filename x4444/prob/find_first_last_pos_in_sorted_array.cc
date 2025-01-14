#include <iostream>
#include <vector>

// 34. Find First and Last Position of Element in Sorted Array
class Solution {
 public:
  int searchL(const std::vector<int>& nums, int target, int e) {
    if (nums[0] == target) return 0;
    int b = 0;
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      if (nums[m] >= target) {
        e = m;
      } else {
        b = m + 1;
      }
    }
    // std::cerr << b << "," << m << "," << e << std::endl;
    if (nums[b] == target) return b;
    return -1;
  }

  int searchR(const std::vector<int>& nums, int target) {
    int b = 0;
    int e = nums.size();
    if (nums[e - 1] == target) return e - 1;
    int m = 0;
    while (b < e) {
      m = b + (e - b) / 2;
      if (nums[m] > target) {
        e = m;
      } else {
        b = m + 1;
      }
    }
    // std::cerr << b << "," << m << "," << e << std::endl;
    if (nums[b - 1] == target) return b - 1;
    return -1;
  }

  std::vector<int> searchRange(const std::vector<int>& nums, int target) {
    int sz = nums.size();
    if (sz == 0) return {-1, -1};
    if (target < nums[0]) return {-1, -1};
    if (target > nums[sz - 1]) return {-1, -1};
    if (sz == 1)
      return nums[0] == target ? std::vector<int>{0, 0}
                               : std::vector<int>{-1, -1};

    int idR = searchR(nums, target);
    if (idR == -1) return {-1, -1};
    if (idR == 0 || nums[idR - 1] != target) return {idR, idR};

    int idL = searchL(nums, target, idR + 1);

    return {idL, idR};
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

void test(const std::vector<int>& nums, int target,
          const std::vector<int> expected) {
  Solution sol;
  std::vector<int> res = sol.searchRange(nums, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 1, {-1, -1});
  test({1}, 5, {-1, -1});
  test({5}, 5, {0, 0});
  test({5, 5}, 5, {0, 1});

  test({10, 10, 10, 20, 20}, 10, {0, 2});
  test({10, 10, 10, 20, 20}, 20, {3, 4});
  test({10, 10, 10, 20, 20}, -10, {-1, -1});
  test({10, 10, 10, 20, 20}, 30, {-1, -1});
  test({10, 10, 10, 20, 20}, 15, {-1, -1});

  test({10, 10, 10, 20, 20, 30, 30}, 10, {0, 2});
  test({10, 10, 10, 20, 20, 30, 30}, 20, {3, 4});
  test({10, 10, 10, 20, 20, 30, 30}, 30, {5, 6});
  test({10, 10, 10, 20, 20, 30, 30}, 5, {-1, -1});
  test({10, 10, 10, 20, 20, 30, 30}, 15, {-1, -1});
  test({10, 10, 10, 20, 20, 30, 30}, 35, {-1, -1});

  test({10, 20, 30}, 10, {0, 0});
  test({10, 20, 30}, 20, {1, 1});
  test({10, 20, 30}, 30, {2, 2});
  test({10, 20, 30}, 5, {-1, -1});
  test({10, 20, 30}, 15, {-1, -1});
  test({10, 20, 30}, 35, {-1, -1});
}
