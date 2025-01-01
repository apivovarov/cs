#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> merge(
      std::vector<std::vector<int>>& intervals) {
    if (intervals.size() < 2) return intervals;
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> res;
    int b = intervals[0][0];
    int e = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i][0] <= e) {
        if (intervals[i][1] > e) e = intervals[i][1];
        continue;
      }
      res.emplace_back(std::vector<int>{b, e});
      b = intervals[i][0];
      e = intervals[i][1];
    }
    res.emplace_back(std::vector<int>{b, e});
    return res;
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

void test(const std::vector<std::vector<int>>& _intervals,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> intervals = _intervals;
  std::vector<std::vector<int>> res = sol.merge(intervals);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{}}, {{}});
  test({{1, 3}}, {{1, 3}});
  test({{1, 3}, {2, 6}, {8, 10}, {15, 18}}, {{1, 6}, {8, 10}, {15, 18}});
  test({{1, 4}, {4, 5}}, {{1, 5}});
  test({{1, 4}, {2, 3}}, {{1, 4}});
}
