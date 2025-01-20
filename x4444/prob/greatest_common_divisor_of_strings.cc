#include <iostream>
#include <string>
#include <numeric>

// Greatest Common Divisor of Strings
class Solution {
 public:
  std::string gcdOfStrings(std::string str1, std::string str2) {
    if (str1 + str2 != str2 + str1) return "";
    int gcd = std::gcd(str1.size(), str2.size());
    return str1.substr(0, gcd);
  }
};

class Solution2 {
 public:
  std::string gcdOfStrings(std::string str1, std::string str2) {
    if (str1.size() == str2.size()) return str1 == str2 ? str1 : "";

    std::string* s1 = &str1;
    std::string* s2 = &str2;

    while (s1->size() != s2->size()) {
      if (s1->size() < s2->size()) {
        std::swap(s1, s2);
      }
      if (s1->find(*s2) != 0) return "";
      (*s1) = s1->substr(s2->size());
    }
    return (*s1 == *s2) ? *s2 : "";
  }
};

void test(const std::string& str1, const std::string& str2,
          const std::string& expected) {
  Solution sol;
  std::string res = sol.gcdOfStrings(str1, str2);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("CXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXN",
       "CXTXNCXTXNCXTXNCXTXNCXTXN", "CXTXN");
  test("CXTXNCXTXNCXTXNCXTXNCXTXN",
       "CXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXNCXTXN",
       "CXTXN");

  test("ABABAB", "ABA", "");
}
