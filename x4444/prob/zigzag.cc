#include <iostream>
#include <string>

class Solution {
 public:
  std::string convert(const std::string& s, int numRows) {
    if (s.size() < 3) return s;
    if (numRows == 1) return s;
    if (s.size() <= numRows) return s;

    std::string res;
    res.reserve(s.size());
    int winSz = numRows * 2 - 2;
    for (int i = 0; i < numRows; ++i) {
      for (int P = 0; P < s.size() + numRows - 2; P += winSz) {
        int a = P - i;
        int b = P + i;
        if (a < s.size() && a >= 0 && i > 0 && i < numRows - 1)
          res.push_back(s[a]);
        if (b < s.size()) res.push_back(s[b]);
      }
    }
    return res;
  }
};

void test(const std::string& s, int numRows, const std::string& expected) {
  Solution sol;
  std::string res = sol.convert(s, numRows);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("A", 1, "A");
  test("AB", 2, "AB");
  test("ABC", 1, "ABC");
  test("ABCD", 2, "ACBD");
  test("ABC", 2, "ACB");
  test("ABCD", 3, "ABDC");
  test("ABCD", 4, "ABCD");
  test("ABCDE", 4, "ABCED");
  test("ABCDEF", 4, "ABFCED");
  test("ABCDEFG", 4, "AGBFCED");
  test("ABCDEFGBCDEFG", 4, "AGGBFBFCECEDD");
  test("ABCBABCBABCB", 3, "AAABBBBBBCCC");
  test("ABCBABCBABC", 3, "AAABBBBBCCC");
  test("ABCBABCBABCBAB", 3, "AAAABBBBBBBCCC");

  test("ABCDCBABCDCBABCD", 4, "AAABBBBBCCCCCDDD");
  test("ABCDCBABCDCBABCDC", 4, "AAABBBBBCCCCCCDDD");
  test("ABCDCBABCDCBABCDCB", 4, "AAABBBBBBCCCCCCDDD");
  test("ABCDCBABCDCBABCDCBA", 4, "AAAABBBBBBCCCCCCDDD");
  test("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
  test("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
}
