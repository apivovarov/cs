#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> insert(
      const std::vector<std::vector<int>>& intervals,
      const std::vector<int>& newInterval) {
    if (intervals.empty() && newInterval.empty()) return {};
    if (intervals.empty()) return {newInterval};
    if (newInterval.empty()) return intervals;

    int b = intervals[0][0];
    int e = intervals[0][1];
    int i = 1;
    bool inserted = false;
    std::vector<std::vector<int>> res;
    if (newInterval[0] <= b) {
      b = newInterval[0];
      e = newInterval[1];
      i = 0;
      inserted = true;
    }

    for (; i < intervals.size(); ++i) {
      int bn;
      int en;
      if (!inserted && newInterval[0] <= intervals[i][0]) {
        bn = newInterval[0];
        en = newInterval[1];
        --i;
        inserted = true;
      } else {
        bn = intervals[i][0];
        en = intervals[i][1];
      }
      if (bn <= e) {
        if (en > e) e = en;
        continue;
      }
      res.push_back({b, e});
      b = bn;
      e = en;
    }
    if (inserted) {
      res.push_back({b, e});
    } else {
      int bn = newInterval[0];
      int en = newInterval[1];
      if (bn <= e) {
        if (en > e) e = en;
        res.push_back({b, e});
      } else {
        res.push_back({b, e});
        res.push_back({bn, en});
      }
    }
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

void test(const std::vector<std::vector<int>>& intervals,
          const std::vector<int>& newInterval,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = sol.insert(intervals, newInterval);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, {}, {});
  test({}, {1, 3}, {{1, 3}});
  test({{1, 3}}, {}, {{1, 3}});
  test({{1, 3}}, {1, 3}, {{1, 3}});
  test({{1, 3}, {5, 8}}, {1, 3}, {{1, 3}, {5, 8}});

  test({{1, 3}, {5, 8}}, {10, 11}, {{1, 3}, {5, 8}, {10, 11}});
  test({{1, 3}, {5, 8}}, {8, 11}, {{1, 3}, {5, 11}});
  test({{1, 3}, {5, 8}}, {7, 11}, {{1, 3}, {5, 11}});

  test({{1, 3}, {5, 8}}, {-3, -1}, {{-3, -1}, {1, 3}, {5, 8}});
  test({{1, 3}, {5, 8}}, {-3, 1}, {{-3, 3}, {5, 8}});
  test({{1, 3}, {5, 8}}, {-3, 2}, {{-3, 3}, {5, 8}});

  test({{1, 3}, {5, 8}, {9, 11}}, {3, 4}, {{1, 4}, {5, 8}, {9, 11}});
  test({{1, 3}, {5, 8}, {9, 11}}, {2, 4}, {{1, 4}, {5, 8}, {9, 11}});
  test({{1, 3}, {5, 8}, {9, 11}}, {3, 5}, {{1, 8}, {9, 11}});
  test({{1, 3}, {5, 8}, {9, 11}}, {3, 6}, {{1, 8}, {9, 11}});
  test({{1, 3}, {5, 8}, {9, 11}}, {3, 9}, {{1, 11}});
  test({{1, 3}, {5, 8}, {9, 11}}, {-1, 7}, {{-1, 8}, {9, 11}});
}
