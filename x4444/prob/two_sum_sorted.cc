#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
    if (numbers.size() < 2) return {};
    int b = 0;
    int e = numbers.size() - 1;
    while (b < e) {
      int sum = numbers[b] + numbers[e];
      if (sum == target) {
        return {b + 1, e + 1};
      } else if (sum < target) {
        ++b;
      } else {
        --e;
      }
    }
    return {};
  }
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vv) {
  os << '[';
  for (int v : vv) os << v << ",";
  os << ']';
  return os;
}

void test(const std::vector<int>& numbers, int target,
          const std::vector<int>& expected) {
  Solution sol;
  std::vector<int> res = sol.twoSum(numbers, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test({2, 7, 11, 15}, 9, {1, 2});
  test({2, 3, 4}, 6, {1, 3});
  test({-1, 0}, -1, {1, 2});
  test({-8, -5, -1, 0, 1}, -9, {1, 3});
}
