#include <iostream>
#include <vector>
#include <climits>

// 120. Triangle
class Solution {
 public:
  int minimumTotal(std::vector<std::vector<int>>& triangle) {
    if (triangle.size() == 1) return triangle[0][0];
    int sz = triangle.size();
    for (int i = 1; i < sz; ++i) {
      int jsz = i + 1;
      for (int j = 0; j < jsz; ++j) {
        int s1 = INT_MAX;
        int s2 = INT_MAX;
        if (j > 0) s1 = triangle[i - 1][j - 1];
        if (j < i) s2 = triangle[i - 1][j];
        int s = s1 < s2 ? s1 : s2;
        triangle[i][j] += s;
      }
    }
    int minPath = INT_MAX;
    int i = sz - 1;
    for (int j = 0; j < sz; ++j) {
      if (triangle[i][j] < minPath) minPath = triangle[i][j];
    }
    return minPath;
  }
};

void test(const std::vector<std::vector<int>>& _tri, int expected) {
  Solution sol;
  std::vector<std::vector<int>> tri = _tri;
  int res = sol.minimumTotal(tri);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}, 11);
  test({{-10}}, -10);
}
