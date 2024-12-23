#include <iostream>
#include <string>

class Solution {
 public:
  int romanToInt(const std::string& s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'I') {
        if (i + 1 < s.size() && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
          res -= 1;
        } else {
          res += 1;
        }
      } else if (s[i] == 'V') {
        res += 5;
      } else if (s[i] == 'X') {
        if (i + 1 < s.size() && (s[i + 1] == 'L' || s[i + 1] == 'C')) {
          res -= 10;
        } else {
          res += 10;
        }
      } else if (s[i] == 'L') {
        res += 50;
      } else if (s[i] == 'C') {
        if (i + 1 < s.size() && (s[i + 1] == 'D' || s[i + 1] == 'M')) {
          res -= 100;
        } else {
          res += 100;
        }
      } else if (s[i] == 'D') {
        res += 500;
      } else if (s[i] == 'M') {
        res += 1000;
      }
    }
    return res;
  }
};

void test(const std::string& s, int expected) {
  Solution sol;
  int res = sol.romanToInt(s);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("", 0);
  test("III", 3);
  test("LVIII", 58);
  test("MCMXCIV", 1994);
}
