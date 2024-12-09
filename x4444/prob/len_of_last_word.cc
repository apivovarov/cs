#include <string>
#include <iostream>

class Solution {
 public:
  int lengthOfLastWord(const std::string& s) {
    if (s.size() == 0) return 0;
    int id = s.size() - 1;
    for (; id >= 0 && s.at(id) == ' '; --id) {
    }
    if (id == -1) return 0;
    int endIdIncl = id;
    for (; id >= 0 && s.at(id) != ' '; --id) {
    }
    return endIdIncl - id;
  }
};

void test(const std::string& s, int expected) {
  Solution sol;
  int res = sol.lengthOfLastWord(s);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("", 0);
  test(" ", 0);
  test("   ", 0);
  test("a  ", 1);
  test(" a  ", 1);
  test("  a", 1);
  test("a", 1);
  test("Hello World", 5);
  test("   fly me   to   the moon  ", 4);
}