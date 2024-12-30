#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
    if (numbers.size() < 2) return {};
    std::unordered_map<int, int> map;
    map.emplace(numbers[0], 0);

    for (int i = 1; i < numbers.size(); ++i) {
      auto it = map.find(target - numbers[i]);
      if (it != map.end()) {
        return {it->second, i};
      }
      map.emplace(numbers[i], i);
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
  test({2, 11, 7, 15}, 9, {0, 2});
  test({3, 2, 4}, 6, {1, 2});
  test({-1, 0}, -1, {0, 1});
  test({0, -5, 1, -8, -1}, -9, {3, 4});
  test({0, -5, 1, -8, -1}, -3, {});
}
