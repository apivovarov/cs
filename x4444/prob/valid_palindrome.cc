#include <iostream>
#include <cctype>
#include <string>

class Solution {
 public:
  bool isPalindrome(const std::string& s) {
    if (s.size() < 2) return true;
    int b = 0;
    int e = s.size() - 1;
    while (b < e) {
      char bc = s[b];
      if (!std::isalnum(bc)) {
        ++b;
        continue;
      }
      char ec = s[e];
      if (!std::isalnum(ec)) {
        --e;
        continue;
      }
      bc = std::tolower(bc);
      ec = std::tolower(ec);
      if (bc != ec) return false;
      ++b;
      --e;
    }
    return true;
  }
};

void test(const std::string& s, bool expected) {
  Solution sol;
  bool res = sol.isPalindrome(s);

  if (res != expected) {
    std::cerr << "ERROR: for str: " << s << std::endl;
  }
}

int main() {
  test("A", true);
  test("AA", true);
  test("Aa", true);
  test("AB", false);
  test("Ab", false);
  test("Aba", true);
  test("A. A", true);
  test("A.bA", true);
  test("A man, a plan, a canal: Panama", true);
  test("race a car", false);
  test(" ", true);
  test("  ", true);
  test("  .", true);
}
