#include <iostream>
#include <string>

class Solution {
 public:
  bool isSubsequence(const std::string& s, const std::string& t) {
    if (s.empty()) return true;
    if (s.size() > t.size()) return false;

    int si = 0;
    for (int ti = 0; ti < t.size(); ++ti) {
      if (t[ti] != s[si]) continue;
      ++si;
      if (si == s.size()) return true;
    }
    return false;
  }
};

void test(const std::string& s, const std::string& t, bool expected) {
  Solution sol;
  bool res = sol.isSubsequence(s, t);
  if (res != expected) {
    std::cerr << "ERROR: s: " << s << ", t: " << t << std::endl;
  }
}

int main() {
  test("", "", true);
  test("", "A", true);
  test("A", "BA", true);
  test("AC", "BABC", true);
  test("BC", "BABC", true);
  test("BA", "BABC", true);
  test("BB", "BABC", true);
  test("CB", "BABC", false);
  test("CA", "BABC", false);
  test("ABC", "ABC", true);
}
