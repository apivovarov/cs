#include <iostream>
#include <string>
#include <vector>

class Solution {
 public:
  inline bool check(std::vector<char>& map, char key, char val) {
    char _val = map[key];
    if (_val == 0) {
      map[key] = val;
      return true;
    }
    return _val == val;
  }

  bool isIsomorphic(const std::string& s, const std::string& t) {
    if (s.size() != t.size()) return false;
    if (s.empty()) return true;
    if (s.size() == 1) return s[0] == t[0];

    std::vector<char> map(256);
    std::vector<char> map_rev(256);

    for (int i = 0; i < s.size(); ++i) {
      if (!check(map, s[i], t[i])) return false;
      if (!check(map_rev, t[i], s[i])) return false;
    }
    return true;
  }
};

void test(const std::string& s, const std::string& t, bool expected) {
  Solution sol;
  bool res = sol.isIsomorphic(s, t);
  if (res != expected) {
    std::cerr << "ERROR: res: " << std::boolalpha << res
              << ", exp: " << expected << ", for: " << s << " " << t
              << std::endl;
  }
}

int main() {
  test("egg", "add", true);
  test("foo", "bar", false);
  test("paper", "title", true);
  test("ffoo", "zaza", false);
  test("ffoo", "zzaa", true);
  test("bbbaaaba", "aaabbbba", false);
  test("badc", "baba", false);
  test("fokl", "baba", false);
}
