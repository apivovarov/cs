#include <iostream>
#include <string>
#include <stack>

class Solution {
 public:
  bool isValid(const std::string& s) {
    if (s.empty()) return true;
    if (s.size() % 2 == 1) return false;
    if (s[0] == ')' || s[0] == '}' || s[0] == ']') return false;
    int e = s.size() - 1;
    if (s[e] == '(' || s[e] == '{' || s[e] == '[') return false;

    std::stack<char> st;
    st.push(s[0]);

    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
        st.push(s[i]);
        continue;
      }
      if (st.empty()) return false;
      char c = st.top();
      st.pop();
      if (s[i] == ')' && c != '(') return false;
      if (s[i] == '}' && c != '{') return false;
      if (s[i] == ']' && c != '[') return false;
    }
    return st.empty();
  }
};

void test(const std::string& s, bool expected) {
  Solution sol;
  if (sol.isValid(s) != expected) {
    std::cerr << "ERROR: for s: " << s << std::endl;
  }
}

int main() {
  test("()", true);
  test("(", false);
  test(")", false);
  test("(()", false);
  test("))(", false);
  test("()))", false);
  test("((()", false);
  test("(())", true);
  test("(({[[()]]}))", true);
  test("(({[[(])]}))", false);
  test("(({[[()]}]))", false);
  test("(({[[()]]]))", false);
}
