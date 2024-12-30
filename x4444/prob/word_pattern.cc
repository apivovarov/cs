#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Solution {
 public:
  bool wordPattern(const std::string& pattern, const std::string& s) {
    std::unordered_map<char, std::string> map;
    std::unordered_map<std::string, char> revmap;
    std::istringstream iss(s);
    std::string w;
    size_t i = 0;
    while (iss >> w) {
      if (i >= pattern.size()) return false;
      char c = pattern[i];

      auto it = map.find(c);
      if (it == map.end()) {
        map.emplace(c, w);
      } else if (w != it->second) {
        return false;
      }

      auto revit = revmap.find(w);
      if (revit == revmap.end()) {
        revmap.emplace(w, c);
      } else if (c != revit->second) {
        return false;
      }
      ++i;
    }
    return i == pattern.size();
  }
};

void test(const std::string& pattern, const std::string& s, bool expected) {
  Solution sol;
  bool res = sol.wordPattern(pattern, s);
  if (expected != res) {
    std::cerr << "ERROR: for: " << pattern << ":" << s << std::endl;
  }
}

int main() {
  test("abba", "dog cat cat dog", true);
  test("abbaa", "dog cat cat dog", false);
  test("abb", "dog cat cat dog", false);
  test("abba", "dog cat cat fish", false);
  test("abba", "dog dog dog dog", false);
  test("bbbb", "dog cat cat dog", false);
}
