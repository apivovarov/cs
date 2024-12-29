#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  inline std::string getKey(std::string s) {
    // To get anogram key we can sort chars - O(n log(n))
    std::sort(s.begin(), s.end());
    return s;
  }

  std::vector<std::vector<std::string>> groupAnagrams(
      const std::vector<std::string>& arr) {
    if (arr.empty()) return {};
    if (arr.size() == 1) return {{arr[0]}};
    // insert to hashmap is O(1)
    std::unordered_map<std::string, std::vector<std::string>> map(arr.size());
    for (const auto& s : arr) {
      map[getKey(s)].push_back(s);
    }

    std::vector<std::vector<std::string>> res;
    // scan hashmap and move underlying vector to res container - O(n)
    for (const auto& key_vec : map) {
      res.push_back(std::move(key_vec.second));
    }
    return res;
  }
};

std::ostream& operator<<(std::ostream& os,
                         std::vector<std::vector<std::string>> res) {
  os << "[";
  for (const auto& vec : res) {
    os << "[";
    for (const auto& s : vec) {
      os << s << ",";
    }
    os << "],";
  }
  os << "]";
  return os;
}

void test(const std::vector<std::string>& arr,
          const std::vector<std::vector<std::string>>& _expected) {
  Solution sol;
  std::vector<std::vector<std::string>> res = sol.groupAnagrams(arr);
  for (std::vector<std::string>& vv : res) {
    std::sort(vv.begin(), vv.end());
  }
  std::sort(res.begin(), res.end());
  std::vector<std::vector<std::string>> expected = _expected;
  for (std::vector<std::string>& vv : expected) {
    std::sort(vv.begin(), vv.end());
  }
  std::sort(expected.begin(), expected.end());
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({"eat", "tea", "tan", "ate", "nat", "bat"},
       {{"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}});

  test({"foo", "bar", "ofo", "bra", "ab", "hello", "ba"},
       {{"foo", "ofo"}, {"bar", "bra"}, {"ab", "ba"}, {"hello"}});
}
