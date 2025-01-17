#include <iostream>
#include <vector>
#include <unordered_set>

// 139. Word Break
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> wd;
    std::unordered_set<int> ld;
    for (auto& w : wordDict) {
      wd.insert(w);
      ld.insert(w.size());
    }
    int ssz = s.size();
    std::vector<int> dp(ssz, -1);
    for (int i = -1; i < ssz - 1; ++i) {
      if (i >= 0 && dp[i] < 0) continue;
      for (int l : ld) {
        int st = i + 1;
        int e_inc = i + l;
        if (e_inc >= ssz) continue;
        std::string k = s.substr(st, l);
        if (wd.count(k) > 0) {
          dp[e_inc] = l;
          if (e_inc == ssz - 1) return true;
        }
      }
    }
    return false;
  }
};

void test(const std::string& s, const std::vector<std::string>& wordDict,
          bool expected) {
  Solution sol;
  bool res = sol.wordBreak(s, wordDict);
  if (res != expected) {
    std::cerr << "ERROR: res: " << std::boolalpha << res << std::endl;
  }
}

int main() {
  test("leetcode", {"leet", "code"}, true);
  test("applepenapple", {"apple", "pen"}, true);
  test("catsandog", {"cats", "dog", "sand", "and", "cat"}, false);
}
