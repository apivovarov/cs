#include <iostream>
#include <vector>

// Bitwise OR of Numbers Range
class Solution {
 public:
  int rangeBitwiseOr(int left, int right) {
    if (left == right) return left;
    int maxInt = (1 << 30) + ((1 << 30) - 1);
    if (left == maxInt || right == maxInt) return maxInt;

    int shift = 0;
    while (left < right) {
      left >>= 1;
      right >>= 1;
      shift++;
    }
    // return original lenght
    left <<= shift;

    // fill tail with 1s
    left |= (1 << shift) - 1;
    return left;
  }
};

class Solution2 {
 public:
  int rangeBitwiseOr(int left, int right) {
    if (left == right) return left;
    int res = 0;
    for (int i = 0; i < 31; ++i) {
      int L = left & 1;
      int R = right & 1;

      res |= L << i;
      R = (R ^ L) & R;
      int Rbit = R << i;
      Rbit = Rbit + (Rbit - R);
      res |= Rbit;

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
  int res = sol.rangeBitwiseOr(left, right);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test(0, 1, 1);
  test(1, 1, 1);
  test(0, 0b0010, 0b0011);
  test(0, 0b0100, 0b0111);
  test(0b0001, 0b0100, 0b0111);
  test(0b0010, 0b0010, 0b0010);
  test(0b00100, 0b10010, 0b11111);
  test(0b10010, 0b10100, 0b10111);
  test(0b10000, 0b10010, 0b10011);
  test(0b01111111111111111111111111110000, 0b01111111111111111111111111111111,
       0b01111111111111111111111111111111);

  test(0b01100111111111111111111111110000, 0b01111111111111111111111111111111,
       0b01111111111111111111111111111111);
}
