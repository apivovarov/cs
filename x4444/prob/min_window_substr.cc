#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
 public:
  std::string minWindow(const std::string& s, const std::string& t) {
    if (s.empty() || t.empty()) return "";

    // Frequency map for characters in t
    std::unordered_map<char, int> charCount;
    for (char c : t) charCount[c]++;

    int required = charCount.size();  // Total distinct characters in t
    int formed = 0;  // Characters in current window that meet the requirement

    std::unordered_map<char, int> windowCount;  // Counts in the current window

    int left = 0, right = 0;  // Window pointers
    int minLen = INT_MAX;
    int startIdx = 0;  // Start index of the minimum window

    while (right < s.size()) {
      // Expand window
      char c = s[right];
      windowCount[c]++;

      if (charCount.count(c) && windowCount[c] == charCount[c]) {
        formed++;
      }

      // Shrink window from left as much as possible while maintaining
      // constraints
      while (left <= right && formed == required) {
        char lc = s[left];

        // Update the minimum window
        if (right - left + 1 < minLen) {
          minLen = right - left + 1;
          startIdx = left;
        }

        // Contract window
        windowCount[lc]--;
        if (charCount.count(lc) && windowCount[lc] < charCount[lc]) {
          formed--;
        }
        left++;
      }

      right++;  // Expand the window
    }

    return minLen == INT_MAX ? "" : s.substr(startIdx, minLen);
  }
};

class Solution2 {
 public:
  std::string minWindow(const std::string& s, const std::string& t) {
    if (s.empty() || t.empty()) return "";
    if (s.size() < t.size()) return "";
    if (s.size() == t.size() && s == t) return s;
    if (t.size() == 1) return s.find(t[0]) == std::string::npos ? "" : t;

    std::unordered_map<char, int> map;
    for (char c : t) {
      ++map[c];
    }

    int winSz = s.size();
    int wb = -1;
    int we = -1;

    int posCnt = t.size();
    int b = 0;
    int e;
    // find start
    while (b < s.size()) {
      auto it = map.find(s[b]);
      if (it != map.end()) {
        --it->second;
        --posCnt;
        break;
      }
      ++b;
    }
    if (b == s.size()) return "";

    e = b;

    // init window
    while (posCnt != 0) {
      ++e;
      while (e < s.size()) {
        auto it = map.find(s[e]);
        if (it != map.end()) {
          --it->second;
          if (it->second >= 0) {
            --posCnt;
          }
          break;
        }
        ++e;
      }

      if (e == s.size()) {
        return "";
      }
    }
    // shrink Begin
    while (b < s.size()) {
      auto it = map.find(s[b]);
      if (it != map.end()) {
        if (it->second == 0) break;
        ++it->second;
      }
      ++b;
    }

    winSz = e - b + 1;
    wb = b;
    we = e;

    // slide window
    while (true) {
      // move Right end
      ++e;
      while (e < s.size()) {
        auto it = map.find(s[e]);
        if (it != map.end()) {
          --it->second;
          break;
        }
        ++e;
      }
      if (e == s.size()) {
        break;
      }

      // shrink Begin
      while (b < s.size()) {
        auto it = map.find(s[b]);
        if (it != map.end()) {
          if (it->second == 0) break;
          ++it->second;
        }
        ++b;
      }

      if (e - b + 1 < winSz) {
        winSz = e - b + 1;
        wb = b;
        we = e;
      }
    }

    return s.substr(wb, we - wb + 1);
  }
};

void test(const std::string& s, const std::string& t,
          const std::string& expected) {
  Solution2 sol;
  std::string res = sol.minWindow(s, t);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("a", "a", "a");
  test("a", "aa", "");
  test("bcdef", "a", "");
  test("bcade", "a", "a");
  test("CBA", "ABC", "CBA");
  test("ADOBECODEBANC", "ABC", "BANC");
  test("ZADOBECODEBANC", "ABC", "BANC");
  test("ZADOBECODEBANCzftBACggt", "ABC", "BAC");
  test("ZADOBEAODEANB", "ABC", "");
  test("AABBAACCCCC", "ABC", "BAAC");
  test("AABAAABBABBAAAACACCCC", "ABC", "BAAAAC");
  test("ABCBBBAAACCCBAACCCCC", "AABC", "CBAA");
  test("ABCBBBAAACCCBAACCCCC", "ABABCC", "BBAAACC");
}
