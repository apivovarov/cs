#include <iostream>
#include <vector>
#include <string>

// 17. Letter Combinations of a Phone Number
class Solution {
 public:
  void backtrack(const std::vector<std::string>& inp, int pos, std::string& ss,
                 std::vector<std::string>& res) {
    if (pos >= inp.size()) {
      res.push_back(ss);
      // std::cerr << ss << std::endl;
      return;
    }

    const std::string& s = inp[pos];
    for (char c : s) {
      ss.push_back(c);
      // std::cerr << c << ": " << s << std::endl;
      backtrack(inp, pos + 1, ss, res);
      ss.pop_back();
    }
  }

  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.empty()) return {};
    std::vector<std::string> letters = {"000", "111", "abc",  "def", "ghi",
                                        "jkl", "mno", "pqrs", "tuv", "wxyz"};

    std::vector<std::string> inp;
    for (char c : digits) {
      inp.push_back(letters[c - '0']);
    }
    std::string ss = "";
    std::vector<std::string> res;
    backtrack(inp, 0, ss, res);
    return res;
  }
};

int main() {
  Solution sol;
  sol.letterCombinations("");
  sol.letterCombinations("9");
  sol.letterCombinations("23");
  sol.letterCombinations("239");
  sol.letterCombinations("2379");
}
