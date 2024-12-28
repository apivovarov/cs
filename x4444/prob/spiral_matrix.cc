#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix) {
    if (matrix.size() == 0) return {};
    if (matrix.size() == 1) return matrix[0];
    std::vector<int> res;
    size_t totalSz = matrix.size() * matrix[0].size();
    res.reserve(totalSz);

    int b = 0;
    int e = matrix[0].size();
    int u = 0;
    int d = matrix.size();

    while (res.size() < totalSz) {
      // peel
      for (int i = b; i < e; ++i) {
        res.push_back(matrix[u][i]);
      }
      for (int i = u + 1; i < d - 1; ++i) {
        res.push_back(matrix[i][e - 1]);
      }
      if (d - u > 1) {
        for (int i = e; i > b; --i) {
          res.push_back(matrix[d - 1][i - 1]);
        }
      }
      if (e - b > 1) {
        for (int i = d - 1; i > u + 1; --i) {
          res.push_back(matrix[i - 1][b]);
        }
      }
      ++b;
      --e;
      ++u;
      --d;
    }
    return res;
  }
};

std::ostream& operator<<(std::ostream& os, std::vector<int> vv) {
  for (int v : vv) std::cerr << v << ",";
  return os;
}

void test(const std::vector<std::vector<int>>& matrix,
          const std::vector<int>& expected) {
  Solution sol;
  std::vector<int> res = sol.spiralOrder(matrix);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test({{}}, {});
  test({{1, 2, 3}}, {1, 2, 3});
  test({{1}, {2}, {3}}, {1, 2, 3});
  test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {1, 2, 3, 6, 9, 8, 7, 4, 5});
  test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}},
       {1, 2, 3, 6, 9, 12, 11, 10, 7, 4, 5, 8});
  test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}},
       {1, 2, 3, 6, 9, 12, 15, 14, 13, 10, 7, 4, 5, 8, 11});
  test({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
       {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10});
}
