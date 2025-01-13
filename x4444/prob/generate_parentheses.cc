
#include <iostream>
#include <string>
#include <vector>

// 22. Generate Parentheses
class Solution {
 public:
  void backtrack(int n, int ocnt, int ccnt, std::string& s,
                 std::vector<std::string>& res) {
    if (s.size() == 2 * n) {
      res.push_back(s);
      return;
    }

    for (char c : {'(', ')'}) {
      int op = 0;
      int cl = 0;
      if (c == '(') {
        if (ocnt >= n) continue;
        op = 1;
      } else {
        if (ocnt - ccnt <= 0) continue;
        cl = 1;
      }
      s.push_back(c);
      backtrack(n, ocnt + op, ccnt + cl, s, res);
      s.pop_back();
    }
  }

  std::vector<std::string> generateParenthesis(int n) {
    std::string s;
    std::vector<std::string> res;
    backtrack(n, 0, 0, s, res);
    return res;
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

void test(int n, std::vector<std::string> expected) {
  Solution sol;
  std::vector<std::string> res = sol.generateParenthesis(n);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test(1, {"()"});
  test(2, {"(())", "()()"});
  test(3, {"((()))", "(()())", "(())()", "()(())", "()()()"});
  test(8, {});
}
