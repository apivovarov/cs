
#include <iostream>
#include <vector>

class Solution {
 public:
  bool isAnagram(const std::string& s, const std::string& t) {
    if (s.size() != t.size()) return false;
    std::vector<int> map(128);
    for (char c : s) {
      ++map[c];
    }
    for (char c : t) {
      if (--map[c] < 0) return false;
    }
    return true;
  }
};

void test(const std::string& s, const std::string& t, bool expected) {
  Solution sol;
  if (expected != sol.isAnagram(s, t)) {
    std::cerr << "ERROR: for s: " << s << ", t: " << t << std::endl;
  }
}

int main() {
  test("foo", "ofo", true);
  test("abc", "cab", true);
  test("abb", "cab", false);
  test("anagram", "nagaram", true);
}
