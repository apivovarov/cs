#include <iostream>
#include <vector>

class Solution {
 public:
  int findMinArrowShots(std::vector<std::vector<int>>& points) {
    if (points.empty()) return 0;
    if (points.size() == 1) return 1;

    std::sort(points.begin(), points.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                return a[1] < b[1];
              });

    int e = points[0][1];
    int res = 1;
    for (int i = 1; i < points.size(); ++i) {
      if (points[i][0] > e) {
        ++res;
        e = points[i][1];
      }
    }
    return res;
  }
};

void test(const std::vector<std::vector<int>>& _points, int expected) {
  Solution sol;
  std::vector<std::vector<int>> points = _points;
  int res = sol.findMinArrowShots(points);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({{1, 2}}, 1);
  test({{1, 2}, {3, 4}}, 2);
  test({{1, 3}, {3, 4}}, 1);
  test({{1, 6}, {2, 8}, {7, 12}}, 2);
  test({{1, 6}, {2, 8}, {7, 12}, {10, 16}}, 2);
  test({{-3, -1}, {1, 6}, {2, 8}, {7, 12}, {10, 16}}, 3);
  test({{-3, -1}, {1, 6}, {2, 8}, {3, 5}, {7, 12}, {10, 16}}, 3);
  test({{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 7}}, 2);
  test({{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 9}}, 1);
  test({{9, 12},
        {1, 10},
        {4, 11},
        {8, 12},
        {3, 9},
        {6, 9},
        {6, 7},
        {29, 32},
        {21, 30},
        {24, 31},
        {28, 32},
        {23, 29},
        {26, 29},
        {26, 27}},
       4);
}
