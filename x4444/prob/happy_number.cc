#include <iostream>
#include <unordered_set>

class Solution {
 public:
  bool isHappy(int n) {
    if (n == 1) return true;
    std::unordered_set<int> visited;
    while (visited.insert(n).second) {
      int s = 0;
      while (n > 0) {
        int d = n % 10;
        s += d * d;
        n /= 10;
      }
      if (s == 1) return true;
      n = s;
    }
    return false;
  }
};

void test(int n, bool expected) {
  Solution sol;
  if (sol.isHappy(n) != expected) {
    std::cerr << "ERROR: for n: " << n << std::endl;
  }
}

int main() {
  test(1, true);
  test(10, true);
  test(19, true);
  test(2, false);
  test(11, false);
  test(3, false);
  test(4, false);
  test(5, false);
  test(6, false);
  test(7, true);
  test(8, false);
  test(9, false);
  test(49, true);
  test(68, true);
  test(82, true);
  test(11118, true);
}
