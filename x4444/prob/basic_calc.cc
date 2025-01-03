#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Solution {
 public:
  std::vector<std::string> to_rpn(const std::string& s) {
    std::vector<std::string> res;
    std::vector<char> st;
    bool beg = true;
    bool up = false;
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      if (c == '(') {
        beg = true;
        up = false;
      } else if (c == '+') {
        st.push_back(c);
        up = true;
        beg = false;
      } else if (c == '-') {
        if (beg) {
          res.push_back("0");
        }
        st.push_back(c);
        beg = false;
        up = true;
      } else if (c == ')') {
        if (!st.empty()) {
          res.push_back(std::string(1, st.back()));
          st.pop_back();
        }
        beg = false;
        up = false;
      } else if (isdigit(c)) {
        std::string num;
        while (i < s.size() && isdigit(s[i])) {
          num.push_back(s[i++]);
        }
        --i;
        res.push_back(std::move(num));
        if (up) {
          res.push_back(std::string(1, st.back()));
          st.pop_back();
        }
        beg = false;
        up = false;
      }
    }
    return res;
  }

  int calculate(const std::string& s) {
    std::vector<std::string> tokens = to_rpn(s);
    if (tokens.empty()) return 0;
    std::vector<int> st;
    for (const std::string& t : tokens) {
      if (t == "+" || t == "-") {
        int rhs = st.back();
        st.pop_back();
        int lhs = st.back();
        st.pop_back();
        int y;
        if (t == "+")
          y = lhs + rhs;
        else
          y = lhs - rhs;
        st.push_back(y);
      } else {
        st.push_back(std::atoi(t.c_str()));
      }
    }
    return st.back();
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void test_to_rpn(const std::string& s,
                 const std::vector<std::string>& expected) {
  Solution sol;
  std::vector<std::string> res = sol.to_rpn(s);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

void test(const std::string& s, int expected) {
  Solution sol;
  int res = sol.calculate(s);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test_to_rpn("1+(4+5)", {"1", "4", "5", "+", "+"});
  test_to_rpn("1+(4-5)", {"1", "4", "5", "-", "+"});
  test_to_rpn("1+(4-5+2)", {"1", "4", "5", "-", "2", "+", "+"});
  test_to_rpn("(1+(4-5+2))", {"1", "4", "5", "-", "2", "+", "+"});
  test_to_rpn("-(4+5)", {"0", "4", "5", "+", "-"});
  test_to_rpn("-4+5", {"0", "4", "-", "5", "+"});
  test_to_rpn("-4-5", {"0", "4", "-", "5", "-"});
  test_to_rpn("-(4-5)", {"0", "4", "5", "-", "-"});
  test_to_rpn("4+5", {"4", "5", "+"});
  test_to_rpn("(4+5)", {"4", "5", "+"});
  test_to_rpn("(-(4+5))", {"0", "4", "5", "+", "-"});
  test_to_rpn("((1+((4+5))))", {"1", "4", "5", "+", "+"});
  test_to_rpn("((1+(-(4+5))))", {"1", "0", "4", "5", "+", "-", "+"});
  test_to_rpn("((1+((-((4+5))))))", {"1", "0", "4", "5", "+", "-", "+"});
  test_to_rpn(" 1 + ( 4 -5 + 2 ) ", {"1", "4", "5", "-", "2", "+", "+"});
  test_to_rpn("-((1+((-((4+5))))))",
              {"0", "1", "0", "4", "5", "+", "-", "+", "-"});

  test_to_rpn("11+(24+345)", {"11", "24", "345", "+", "+"});
  test_to_rpn("24+345", {"24", "345", "+"});
  test_to_rpn("24", {"24"});
  test_to_rpn("-24", {"0", "24", "-"});

  test_to_rpn("1+(4-345)", {"1", "4", "345", "-", "+"});
  test_to_rpn("1+(-24-345)", {"1", "0", "24", "-", "345", "-", "+"});

  test_to_rpn("1 + 1", {"1", "1", "+"});
  test_to_rpn(" 2-1 + 2 ", {"2", "1", "-", "2", "+"});
  test_to_rpn("(1+(4+5+2)-3)+(6+8)", {"1", "4", "5", "+", "2", "+", "+", "3",
                                      "-", "6", "8", "+", "+"});

  test("1 + 1", 2);
  test(" 2-1 + 2 ", 3);
  test("(1+(4+5+2)-3)+(6+8)", 23);
}
