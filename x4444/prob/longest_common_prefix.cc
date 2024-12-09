#include <vector>
#include <string>
#include <iostream>

class Solution {
 public:
  std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    if (strs.size() == 0) return "";
    if (strs.size() == 1) return strs[0];
    if (strs[0] == "") return "";

    int i = 0;
    for (; i < strs[0].size(); ++i) {
      char c = strs[0].at(i);
      for (int j = 1; j < strs.size(); ++j) {
        if (i < strs[j].size() && c == strs[j].at(i)) {
          // good
        } else {
          return strs[0].substr(0, i);
        }
      }
    }
    return strs[0];
  }
};

void test(const std::vector<std::string>& vec, const std::string& expected) {
  Solution sol;
  auto res = sol.longestCommonPrefix(vec);
  if (res != expected) {
    std::cout << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, "");
  test({""}, "");
  test({"aaa"}, "aaa");
  test({"aaa", "aaa", "aa"}, "aa");
  test({"aaa", "aaa", "aab"}, "aa");
  test({"aaa", "aaa", "aabb"}, "aa");
  test({"aaa", "bcd", "bcd"}, "");
}