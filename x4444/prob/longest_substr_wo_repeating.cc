#include <iostream>
#include <string>
#include <unordered_set>

class Solution {
 public:
  int lengthOfLongestSubstring(const std::string& s) {
    if (s.empty()) return 0;
    if (s.size() == 1) return 1;
    if (s.size() == 2) return s[0] == s[1] ? 1 : 2;

    int b = 0;
    std::unordered_set<char> ss;
    ss.insert(s[0]);
    int maxS = 1;

    for (int i = 1; i < s.size(); ++i) {
      while (ss.find(s[i]) != ss.end()) {
        ss.erase(s[b]);
        ++b;
      }
      ss.insert(s[i]);
      if (ss.size() > maxS) maxS = ss.size();
    }
    return maxS;
  }
};

void test(const std::string& s, int expected) {
  Solution sol;
  int res = sol.lengthOfLongestSubstring(s);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test("", 0);
  test("A", 1);
  test("AB", 2);
  test("AAB", 2);
  test("ABB", 2);
  test("AABB", 2);
  test("ABCBA", 3);
  test("ABCBABCCBAD", 4);
  test("DABCBABCCBA", 4);
  test("ABCBABCDCBA", 4);
  test("AAAA", 1);
  test("ABCD", 4);
  test("abcabcbb", 3);
  test("pwwkew", 3);
}
