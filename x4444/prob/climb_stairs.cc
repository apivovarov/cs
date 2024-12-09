#include <vector>
#include <iostream>

class Solution {
 public:
  int climbStairs(int n) {
    if (n <= 0) return 1;
    std::vector<int> vec(n + 1);
    vec[0] = 1;
    vec[1] = 1;
    for (int i = 2; i <= n; ++i) {
      vec[i] = vec[i - 1] + vec[i - 2];
    }
    return vec[n];
  }
};

void test(int n, int expected) {
  Solution sol;
  int res = sol.climbStairs(n);
  if (res != expected) {
    std::cerr << "ERROR: Bad res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test(2, 2);
  test(3, 3);
  test(4, 5);
}