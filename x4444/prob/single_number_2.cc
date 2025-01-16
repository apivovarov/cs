#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "] ";
  return os;
}

// 136. Single Number II
class Solution {
 public:
  int singleNumber(const std::vector<int>& nums) {
    std::vector<int> stats(32);

    for (int v : nums) {
      // count sign bit and down it (needed for right shift)
      stats[31] += (v >> 31) & 1;
      v &= 0b01111111111111111111111111111111;
      // count renaining bits
      for (int i = 0; i < 31 && v; ++i) {
        stats[i] += v & 1;
        v >>= 1;
      }
    }

    // std::cerr << stats << std::endl;

    int res = 0;
    for (int i = 0; i < 32; ++i) {
      res |= (stats[i] % 3) << i;
    }
    return res;
  }
};

void test(const std::vector<int>& nums, int expected) {
  Solution sol;
  int res = sol.singleNumber(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  int a = 0b01111111111111111111111111111111;
  int b = 0b11111111111111111111111111111111;
  int c = 0b10000000000000000000000000000000;
  test({1}, 1);
  test({2, 2, 1, 2}, 1);
  test({1, 4, 1, 2, 2, 1, 2}, 4);
  test({a, 1, 1, 1}, a);
  test({b, 1, 1, 1}, b);
  test({c, 1, 1, 1}, c);
  test({-1}, -1);
  test({-1, 1, 1, 1}, -1);
  test({-1000001, 1, 1, 1}, -1000001);
  test({1000001, 1, 1, 1}, 1000001);
  test({12345678, 1, 1, 1}, 12345678);
  test({-12345678, 1, 1, 1}, -12345678);
  test({4}, 4);
  test({44, 4, 44, 44}, 4);
}
