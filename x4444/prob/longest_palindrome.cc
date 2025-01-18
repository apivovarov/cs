#include <iostream>
#include <string>
#include <vector>

// 5. Longest Palindromic Substring
class Solution {
 public:
  std::string longestPalindrome(const std::string& s) {
    int sz = s.size();
    if (sz < 2) return s;
    if (sz == 2) return s[0] == s[1] ? s : s.substr(0, 1);

    std::vector<std::vector<bool>> dp(sz, std::vector<bool>(sz));
    int b = 0;
    int maxL = 1;

    // two diagonals
    dp[0][0] = true;
    for (int i = 1; i < sz; ++i) {
      dp[i][i] = true;
      if (s[i] == s[i - 1]) {
        dp[i][i - 1] = true;
        maxL = 2;
        b = i - 1;
      }
    }

    int badCnt = 0;
    for (int st = 2; st < sz; ++st) {
      int i = st;
      int j = 0;
      bool found = false;
      for (; i < sz; ++i, ++j) {
        if (dp[i - 1][j + 1] && s[i] == s[j]) {
          dp[i][j] = true;
          maxL = st + 1;
          b = j;
          found = true;
          badCnt = 0;
        }
      }
      if (!found) badCnt++;
      if (badCnt >= 2) break;
    }
    return s.substr(b, maxL);
  }
};

void test(const std::string& s, const std::string& expected) {
  Solution sol;
  auto res = sol.longestPalindrome(s);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("", "");
  test("a", "a");
  test("aa", "aa");
  test("ak", "a");
  test("aba", "aba");
  test("kaa", "aa");
  test("kaba", "aba");
  test("aak", "aa");
  test("abak", "aba");
  test("zaak", "aa");
  test("zabak", "aba");
  test("aabazdrabaa", "aba");
  test("babad", "aba");  // or bab
  test("aaca", "aca");
}
