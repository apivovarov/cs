#include <iostream>
#include <vector>

// 201. Bitwise AND of Numbers Range
class Solution {
 public:
  int rangeBitwiseAnd(int left, int right) {
    if (left == 0 || right == 0) return 0;
    if (left == right) return left;
    int shift = 0;
    // Find the common prefix
    while (left && left < right) {
      left >>= 1;
      right >>= 1;
      ++shift;
    }
    // Shift back to the original position
    return left << shift;
  }
};

class Solution2 {
 public:
  int rangeBitwiseAnd(int left, int right) {
    if (left == 0 || right == 0) return 0;
    if (left == right) return left;
    if ((left < (1 << 30)) && (right >= left * 2)) return 0;
    int res = 0;
    for (int i = 0; i < 31 && right; ++i) {
      int L = left & 1;
      int R = right & 1;

      // 1,1 case - set 1
      int bit = (L & R) << i;
      res |= bit;

      // 0,1 case - set [i..0] bits to 0
      R = (R ^ L) & R;
      R = -R;
      res ^= R & res;

      left >>= 1;
      right >>= 1;
    }
    return res;
  }
};

void test(int left, int right, int expected) {
  if (left > right) {
    std::cerr << "ERROR: bad input" << std::endl;
    return;
  }
  Solution sol;
  int res = sol.rangeBitwiseAnd(left, right);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test(0, 1, 0);
  test(1, 1, 1);
  test(1, 0b0010, 0);
  test(1, 0b0100, 0);
  test(0b0101, 0b0101, 0b0101);
  test(0b0100, 0b0101, 0b0100);
  test(0b0010, 0b0010, 0b0010);
  test(0b00100, 0b10010, 0);

  test(0b10010, 0b10100, 0b10000);
  test(0b10000, 0b10010, 0b10000);
  test(0b01111111111111111111111111110000, 0b01111111111111111111111111111111,
       0b01111111111111111111111111110000);

  test(0b01100111111111111111111111110000, 0b01111111111111111111111111111111,
       0b01100000000000000000000000000000);

  test(0b0101, 0b0111, 0b0100);
  test(1, 0b01111111111111111111111111111111, 0);

  test(0b00001111, 0b01111111, 0);
}
