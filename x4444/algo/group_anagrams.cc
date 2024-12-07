#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::string getKey(std::string s) {
  // To get anogram key we can sort chars - O(n log(n))
  std::sort(s.begin(), s.end());
  return s;
}

std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& arr) {
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
    if (!key_vec.second.empty()) {
      res.push_back(std::move(key_vec.second));
    }
  }
  return res;
}

void dump(const std::vector<std::vector<std::string>> & res) {
  std::cout << "[";
  for (const auto& vec : res) {
    std::cout << "[";
    for (const auto& s : vec) {
      std::cout << s << ",";
    }
    std::cout << "],";
  }
  std::cout << "]";
  std::cout << std::endl;
}

int main() {
  std::vector<std::string> arr = {"foo", "bar",   "ofo", "bra",
                                  "ab",  "hello", "ba"};
  std::vector<std::vector<std::string>> res = group_anagrams(arr);
  dump(res);
  dump(group_anagrams(std::vector<std::string>{"foo"}));
}
