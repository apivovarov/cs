#include <iostream>
#include <string>

// 67. Add Binary
class Solution {
 public:
  std::string addBinary(const std::string& a, const std::string& b) {
    std::string resS;

    int asz = a.size();
    int bsz = b.size();
    int jsz = asz > bsz ? asz : bsz;

    char carry = 0;
    for (int i = 0; i < jsz; ++i) {
      char ac = i < asz ? a[asz - i - 1] - '0' : 0;
      char bc = i < bsz ? b[bsz - i - 1] - '0' : 0;
      char yc = ac + bc + carry;
      // std::cerr << ac << " " << bc << " "  << yc << std::endl;
      carry = yc / 2;
      yc %= 2;
      resS.push_back(yc + '0');
    }
    if (carry) {
      resS.push_back('1');
    }
    std::reverse(resS.begin(), resS.end());
    return resS;
  }
};

void test(const std::string& a, const std::string& b,
          const std::string& expected) {
  Solution sol;
  std::string res = sol.addBinary(a, b);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("0", "1", "1");
  test("1", "0", "1");
  test("0", "0", "0");
  test("1", "1", "10");
  test("11", "1", "100");
  test("10", "1", "11");
  test("100", "1", "101");
  test("100", "10", "110");
  test("100", "11", "111");
  test("11", "100", "111");
  test("111", "111", "1110");
  test("100", "100", "1000");
  test("1010", "1011", "10101");
}
