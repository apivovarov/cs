#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

class Solution {
 public:
  bool check(const std::string& s, int b, const std::vector<std::string>& words,
             const std::unordered_map<std::string, int>& _map) {
    int W = words[0].size();
    std::unordered_map<std::string, int> map = _map;
    while (b + W <= s.size()) {
      auto it = map.find(s.substr(b, W));
      if (it == map.end()) return false;
      if (it->second > 1) {
        --(it->second);
      } else {
        map.erase(it);
      }
      if (map.empty()) return true;
      b += W;
    }
    return false;
  }

  std::vector<int> findSubstring(const std::string& s,
                                 const std::vector<std::string>& words) {
    if (s.empty()) return {};
    int W = words[0].size();
    int L = W * words.size();
    if (L == 0) return {};
    if (s.size() < L) return {};
    const char* ch0ptr = s.data();

    std::unordered_map<std::string, int> map;
    for (const std::string& s : words) {
      ++map[s];
    }

    std::unordered_set<int> res;
    for (int i = 0; i <= s.size() - L; ++i) {
      if (res.find(i) != res.end()) continue;
      if (check(s, i, words, map)) {
        res.insert(i);
        int i2 = i;
        while (i2 <= s.size() - L - W) {
          if (strncmp(ch0ptr + i2, ch0ptr + i2 + L, W) != 0) break;
          i2 += W;
          res.insert(i2);
        }
      }
    }
    return std::vector<int>(res.begin(), res.end());
  }
};

std::ostream& operator<<(std::ostream& os, std::vector<int> vv) {
  for (int v : vv) std::cerr << v << ",";
  return os;
}

void test(const std::string& s, const std::vector<std::string>& words,
          const std::vector<int>& expected) {
  Solution sol;
  std::vector<int> res = sol.findSubstring(s, words);
  std::sort(res.begin(), res.end());
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", exp: " << expected << std::endl;
  }
}

int main() {
  test("", {}, {});
  test("b", {"a", "b"}, {});
  test("bar", {"bar"}, {0});
  test("barfoothefoobarman", {"foo", "bar"}, {0, 9});
  test("wordgoodgoodgoodbestword", {"word", "good", "best", "word"}, {});
  test("barfoofoobarthefoobarman", {"bar", "foo", "the"}, {6, 9, 12});
  {
    std::string s(14, 'a');
    std::vector<int> ex(11);
    std::iota(ex.begin(), ex.end(), 0);
    test(s, {"aa", "aa"}, ex);
  }
  {
    std::string s(10000, 'a');
    std::vector<std::string> sa(5000, "a");
    std::vector<int> ex(5001);
    std::iota(ex.begin(), ex.end(), 0);
    test(s, sa, ex);
  }
}
