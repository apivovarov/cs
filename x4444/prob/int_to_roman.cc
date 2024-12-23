#include <iostream>
#include <string>

class Solution {
 public:
  std::string intToRoman(int num) {
    std::string res = "";
    while (num > 0) {
      if (num >= 1000) {
        res.append("M");
        num -= 1000;
      } else if (num >= 900) {
        res.append("CM");
        num -= 900;
      } else if (num >= 500) {
        res.append("D");
        num -= 500;
      } else if (num >= 400) {
        res.append("CD");
        num -= 400;
      } else if (num >= 100) {
        res.append("C");
        num -= 100;
      } else if (num >= 90) {
        res.append("XC");
        num -= 90;
      } else if (num >= 50) {
        res.append("L");
        num -= 50;
      } else if (num >= 40) {
        res.append("XL");
        num -= 40;
      } else if (num >= 10) {
        res.append("X");
        num -= 10;
      } else if (num >= 9) {
        res.append("IX");
        num -= 9;
      } else if (num >= 5) {
        res.append("V");
        num -= 5;
      } else if (num >= 4) {
        res.append("IV");
        num -= 4;
      } else {
        res.append("I");
        num -= 1;
      }
    }
    return res;
  }
};

void test(int num, const std::string& expected) {
  Solution sol;
  const auto& res = sol.intToRoman(num);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test(1, "I");
  test(3, "III");
  test(4, "IV");
  test(5, "V");
  test(7, "VII");
  test(9, "IX");
  test(10, "X");
  test(12, "XII");
  test(14, "XIV");

  test(58, "LVIII");
  test(1994, "MCMXCIV");
  test(3749, "MMMDCCXLIX");
  test(3999, "MMMCMXCIX");
}
