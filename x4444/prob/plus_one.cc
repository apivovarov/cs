#include <iostream>
#include <vector>

// 66. Plus One
class Solution {
 public:
  std::vector<int> plusOne(const std::vector<int>& digits) {
    std::vector<int> res;
    int c = 1;
    auto it = digits.rbegin();
    while (it != digits.rend()) {
      int r = *it + c;
      c = r / 10;
      r %= 10;
      res.push_back(r);
      ++it;
    }
    if (c) {
      res.push_back(1);
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};

void test(const std::vector<int>& digits, const std::vector<int>& expected) {
  Solution sol;
  std::vector<int> res = sol.plusOne(digits);
  if (res != expected) {
    std::cerr << "ERROR:" << std::endl;
  }
}

int main() {
  test({1, 2, 3}, {1, 2, 4});
  test({4, 3, 2, 1}, {4, 3, 2, 2});
  test({9}, {1, 0});
  test({9, 9}, {1, 0, 0});
  test({8, 9}, {9, 0});
}
