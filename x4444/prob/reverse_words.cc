#include <iostream>
#include <string>

class Solution {
 public:
  std::string reverseWords(const std::string& s) {
    if (s.empty()) return s;
    if (s.size() == 1) return s[0] == ' ' ? "" : s;
    std::string res;
    res.reserve(s.size());
    int e = -1;
    for (int i = s.size(); i > 0; --i) {
      if (e == -1) {
        if (s[i - 1] != ' ') e = i;
        continue;
      }
      if (s[i - 1] != ' ') continue;
      if (res.size() > 0) res.append(" ");
      res.append(s.data() + i, e - i);
      e = -1;
    }
    if (e != -1) {
      if (res.size() > 0) res.append(" ");
      res.append(s.data(), e);
    }
    return res;
  }
};

void test(const std::string& s, const std::string& expected) {
  Solution sol;
  std::string res = sol.reverseWords(s);
  if (res != expected) {
    std::cerr << "ERROR: res '" << res << "', expected: '" << expected << "'"
              << std::endl;
  }
}

int main() {
  test("", "");
  test("A", "A");
  test(" A", "A");
  test("A ", "A");
  test(" A ", "A");
  test("A B", "B A");
  test("the sky is blue", "blue is sky the");
  test("  hello world  ", "world hello");
  test("a good   example", "example good a");
  test("     the     sky is    blue  ", "blue is sky the");
  test("  hello    world  ", "world hello");
  test("  a    good   example  ", "example good a");
}
