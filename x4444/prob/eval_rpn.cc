#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Solution {
 public:
  int evalRPN(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return 0;
    std::vector<int> st;
    for (const std::string& t : tokens) {
      if (t == "+" || t == "-" || t == "*" || t == "/") {
        int rhs = st.back();
        st.pop_back();
        int lhs = st.back();
        st.pop_back();
        int y;
        if (t == "+")
          y = lhs + rhs;
        else if (t == "-")
          y = lhs - rhs;
        else if (t == "*")
          y = lhs * rhs;
        else
          y = lhs / rhs;
        st.push_back(y);
      } else {
        st.push_back(std::atoi(t.c_str()));
      }
    }
    return st.back();
  }
};

void test(const std::vector<std::string>& tokens, int expected) {
  Solution sol;
  int res = sol.evalRPN(tokens);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({"18"}, 18);
  test({"2", "1", "+", "3", "*"}, 9);
  test({"4", "13", "5", "/", "+"}, 6);
  test({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"},
       22);
  test({"-2", "-1", "+", "3", "*"}, -9);
}
