#include <iostream>
#include <cmath>

// 9. Palindrome Number
class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x < 10) return true;
    if (x % 10 == 0) return false;

    int rev = 0;

    while (x > rev) {
      rev = rev * 10 + x % 10;
      x /= 10;
    }
    return x == rev || x == rev / 10;
  }
};

void test(int x, bool expected) {
  Solution sol;
  bool res = sol.isPalindrome(x);
  if (res != expected) {
    std::cerr << "ERROR: x: " << x << ", res: " << std::boolalpha << res
              << std::endl;
  }
}

int main() {
  test(1000021, false);
  test(10000201, false);
  test(14000201, false);
  test(120, false);
  test(121, true);
  test(1221, true);
  test(1121, false);
  test(-121, false);
  test(11, true);
  test(1221, true);
  test(1, true);
  test(12321, true);
  test(12331, false);
  test(1234567899, false);
  test(2147483647, false);
  test(2147483646, false);
  test(2147483412, false);
  test(2143223412, true);
}
