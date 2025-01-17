#include <iostream>
#include <cmath>

// 50. Pow(x, n)
class Solution {
 public:
  double _pow(double x, unsigned n) {
    if (n == 1)
      return x;
    else if (n == 2)
      return x * x;
    else if (n == 3)
      return x * x * x;

    double r = _pow(x, n / 2);
    if (n % 2 == 0) {
      return r * r;
    } else {
      return r * r * x;
    }
  }

  double myPow(double x, int n) {
    if (x == 0.0) return n > 0 ? 0.0 : std::nan("");
    if (n == 0) return x > 0.0 ? 1.0 : -1.0;
    unsigned p;
    if (n == -2147483648) {
      p = 2147483648;
    } else {
      p = n > 0 ? n : -n;
    }
    double res = _pow(x, p);
    return n > 0 ? res : (1.0 / res);
  }
};

void test(double x, int n) {
  Solution sol;
  double res = sol.myPow(x, n);

  double expected = std::pow(x, n);
  double diff = (res - expected) / expected;
  if (diff < 0.0) diff = -diff;
  if (diff > 0.000001) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << ", diff: " << diff << std::endl;
  }
}

int main() {
  for (int n = 0; n < 100; ++n) {
    test(0.001, n);
    test(0.001, -n);
    test(1.001, n);
    test(1.001, -n);
  }
  int max = INT_MAX;
  test(1.0000000000001, max);
  test(1.0000000000001, -max);
  test(0.999999999999, max);
  test(0.999999999999, -max);
}
