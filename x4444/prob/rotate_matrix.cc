#include <iostream>
#include <vector>

class Solution {
 public:
  void rotate(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return;
    int n = matrix.size();
    if (n == 1) return;
    for (int b = 0; b < n / 2; b++) {
      int e = n - 1 - b;
      for (int i = 0; i < (e - b); ++i) {
        int p0first = b;
        int p0second = b + i;

        int p1first = e - i;
        int p1second = b;

        int p2first = e;
        int p2second = e - i;

        int p3first = b + i;
        int p3second = e;

        std::swap(matrix[p0first][p0second], matrix[p3first][p3second]);
        std::swap(matrix[p1first][p1second], matrix[p0first][p0second]);
        std::swap(matrix[p2first][p2second], matrix[p1first][p1second]);
      }
    }
  }
};

void test(const std::vector<std::vector<int>>& matrix,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = matrix;
  sol.rotate(res);
  if (res != expected) {
    std::cerr << "ERROR: " << std::endl;
  }
}

int main() {
  test({}, {});
  test({{5}}, {{5}});
  test({{1, 2}, {3, 4}}, {{3, 1}, {4, 2}});
  test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
  test({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
       {{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}});
  test({{1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}},
       {{21, 16, 11, 6, 1},
        {22, 17, 12, 7, 2},
        {23, 18, 13, 8, 3},
        {24, 19, 14, 9, 4},
        {25, 20, 15, 10, 5}});
}
