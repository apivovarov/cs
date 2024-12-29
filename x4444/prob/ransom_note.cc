#include <iostream>
#include <string>

class Solution {
 public:
  bool canConstruct(const std::string& ransomNote,
                    const std::string& magazine) {
    if (magazine.size() < ransomNote.size()) return false;

    std::array<int, 128> map = {};
    for (char c : magazine) {
      ++map[c];
    }

    for (char c : ransomNote) {
      if (map[c]-- <= 0) return false;
    }
    return true;
  }
};

void test(const std::string& ransomNote, const std::string& magazine,
          bool expected) {
  Solution sol;
  bool res = sol.canConstruct(ransomNote, magazine);
  if (res != expected) {
    std::cerr << std::boolalpha << "ERRROR: res: " << res
              << ", expected: " << expected << std::endl;
  }
}

int main() {
  test("a", "b", false);
  test("aa", "ab", false);
  test("aa", "aab", true);
  test("hello world", " wohellrldo d h", true);
  test("hello world", " wohellrdo d h", false);
}
