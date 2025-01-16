#include <iostream>

// 191. Number of 1 Bits
class Solution {
 public:
  int hammingWeight(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 0b01111111111111111111111111111111) return 31;

    int res = 0;
    while (n) {
      res += n & 1;
      n >>= 1;
    }
    return res;
  }
};

void test(int n, int expected) {
  Solution sol;
  int res = sol.hammingWeight(n);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test(0b00000000000000000000000000000000, 0);
  test(0b00000000000000000000000000000001, 1);
  test(0b00000000000000000000000000000010, 1);
  test(0b00000000000000000000000000000011, 2);
  test(0b00000000000000000000000000000100, 1);

  test(0b01000000000000000000000000000000, 1);
  test(0b01100000000000000000000000000000, 2);
  test(0b00100000000000000000000000000000, 1);
  test(0b01111111111111111111111111111111, 31);
  test(0b01111111111111111111111111110111, 30);
}
