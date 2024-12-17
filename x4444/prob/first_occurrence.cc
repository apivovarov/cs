#include <iostream>
#include <string>

// TODO: Add Knuth-Morris-Pratt (KMP) based solution
class Solution {
 public:
  int strStr(std::string s0, std::string s1) {
    if (s1.empty()) return 0;
    if (s0.length() < s1.length()) return -1;
    if (s0 == s1) return 0;

    int p1 = 0;
    for (int p0 = 0; p0 < s0.length(); ++p0) {
      if (s0[p0] == s1[p1]) {
        if (p1 == s1.length() - 1) return p0 - p1;
        ++p1;
      } else if (p1 > 0) {
        p0 -= p1;
        p1 = 0;
      }
    }
    return -1;
  }
};

void test(const std::string& s0, const std::string& s1, int expected) {
  Solution sol;
  int res = sol.strStr(s0, s1);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test("A", "", 0);
  test("", "A", -1);
  test("A", "AA", -1);
  test("A", "A", 0);
  test("AB", "A", 0);
  test("BA", "A", 1);
  test("BAAAB", "AAA", 1);
  test("BAABB", "AAA", -1);
  test("BAABAAAB", "AAA", 4);
  test("BABABACB", "ABAC", 3);
  test("mississippi", "issip", 4);
}
