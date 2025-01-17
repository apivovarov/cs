#include <iostream>
#include <climits>

// 69. Sqrt(x)
class Solution {
 public:
  int mySqrt(int x) {
    if (x == 0) return 0;
    if (x < 4) return 1;
    if (x < 9) return 2;
    if (x < 16) return 3;
    if (x < 25) return 4;
    int b = 2;
    int e = x;
    if (e > 46341) e = 46341;
    int m = 2;
    while (b < e) {
      m = b + (e - b) / 2;
      int cu = m * m;
      if (cu == x) return m;
      if (cu > x)
        e = m;
      else
        b = m + 1;
    }
    if (m * m > x) return m - 1;
    return m;
  }
};

void test(int x) {
  Solution sol;
  int res = sol.mySqrt(x);

  int expected = int(std::sqrt(x));
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  for (int i = 0; i < 120; ++i) {
    test(i);
  }
  int max = INT_MAX;
  test(max);
  test(max / 2);
  test(max - 4);
}
