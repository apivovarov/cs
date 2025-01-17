#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <numeric>

namespace std {
template <>
struct hash<std::pair<int, int>> {
  size_t operator()(const std::pair<int, int>& p) const {
    std::hash<int> hh;
    auto h1 = hh(p.first);
    auto h2 = hh(p.second);
    return (h1) ^ (h2 << 1);
  }
};
}  // namespace std

// 149. Max Points on a Line
class Solution {
 public:
  int maxPoints(const std::vector<std::vector<int>>& points) {
    int globMax = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
      auto& a = points[i];
      std::unordered_map<std::pair<int, int>, int> freq;
      int max = 0;
      for (int j = i + 1; j < points.size(); ++j) {
        auto& b = points[j];

        // slope pair  (sort points first)
        std::pair<int, int> slope;
        if (a < b) {
          slope.first = b[0] - a[0];
          slope.second = b[1] - a[1];
        } else {
          slope.first = a[0] - b[0];
          slope.second = a[1] - b[1];
        }
        if (slope.first == 0) {
          slope.second = INT_MAX;
        } else {
          int gcd = std::gcd(slope.first, slope.second);
          slope.first /= gcd;
          slope.second /= gcd;
        }

        int& fr = freq[slope];
        ++fr;
        std::cerr << a[0] << a[1] << " " << b[0] << b[1] << " " << slope.first
                  << slope.second << std::endl;
        if (fr > max) max = fr;
      }
      if (max > globMax) globMax = max;
    }
    return globMax + 1;
  }
};

void test(const std::vector<std::vector<int>>& points, int expected) {
  Solution sol;
  int res = sol.maxPoints(points);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{1, 1}, {2, 2}, {3, 3}}, 3);
  test({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}, 4);
  test({{0, 0}, {94911151, 94911150}, {94911152, 94911151}}, 2);

  test({{1, 1}, {3, 2}, {5, 3}, {6, -1}, {2, 3}, {-1, 6}}, 4);
  test({{-6, -1}, {3, 1}, {12, 3}}, 3);
}
