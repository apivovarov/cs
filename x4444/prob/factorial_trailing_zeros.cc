#include <iostream>

// 172. Factorial Trailing Zeroes
class Solution {
 public:
  int trailingZeroes(int n) {
    if (n < 5) return 0;
    int p = 5;
    int res = 0;
    while (n >= p) {
      res += n / p;
      p *= 5;
    }
    return res;
  }
};

int main() {
  Solution sol;
  std::cerr << sol.trailingZeroes(5) << std::endl;
  std::cerr << sol.trailingZeroes(21) << std::endl;
  std::cerr << sol.trailingZeroes(26) << std::endl;
  std::cerr << sol.trailingZeroes(126) << std::endl;
}
