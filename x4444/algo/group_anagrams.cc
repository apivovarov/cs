#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

std::string getKey(std::string s) {
  // To get anogram key we can sort chars - O(n log(n))
  std::sort(s.begin(), s.end());
  return s;
}

std::vector<std::vector<std::string>> process(std::vector<std::string>& arr) {
  // insert to hashmap is O(1)
  std::unordered_map<std::string, std::vector<std::string>> map(arr.size());
  for (auto& s : arr) {
    map[getKey(s)].push_back(s);
  }

  std::vector<std::vector<std::string>> res;
  // scan hashmap and move underlying vector to res container - O(n)
  for (auto& key_vec : map) {
    if (!key_vec.second.empty()) {
      res.push_back(std::move(key_vec.second));
    }
  }
  return res;
}

int main() {
  std::vector<std::string> arr = {"foo", "bar",   "ofo", "bra",
                                  "ab",  "hello", "ba"};
  std::vector<std::vector<std::string>> res = process(arr);
  std::cout << "[";
  for (const auto& vec : res) {
    std::cout << "[";
    for (const auto& s : vec) {
      std::cout << s << ",";
    }
    std::cout << "]";
  }
  std::cout << "]";
  std::cout << std::endl;
}
