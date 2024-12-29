#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Solution {
 public:
  bool makeAdj(const std::vector<std::pair<char, char>>& pairs, char& sourceC,
               std::unordered_map<char, std::vector<char>>& adj) {
    std::unordered_set<char> dest;
    std::unordered_map<char, std::unordered_set<char>> _adj;
    for (const auto& p : pairs) {
      _adj[p.first].insert(p.second);
      dest.insert(p.second);
    }

    adj.reserve(_adj.size());
    sourceC = -1;
    for (const auto& ent : _adj) {
      adj[ent.first] = std::vector<char>(ent.second.begin(), ent.second.end());
      if (dest.find(ent.first) == dest.end()) {
        if (sourceC != -1) {
          std::cerr << "ERROR: source node already found. old: " << sourceC
                    << ", new: " << ent.first << std::endl;
          return false;
        } else {
          sourceC = ent.first;
        }
      }
    }
    if (sourceC == -1) {
      std::cerr << "ERROR: source node not found." << std::endl;
      return false;
    }
    // Insert all missing dest nodes to adj as keys with empty value
    for (char c : dest) {
      adj[c];
    }
    return true;
  }

  bool dfs(const std::unordered_map<char, std::vector<char>>& adj,
           std::unordered_set<char>& visited, std::unordered_set<char>& temp,
           std::vector<char>& res, const char c) {
    if (visited.find(c) != visited.end()) return true;
    if (!temp.insert(c).second) {
      std::cerr << "ERROR: cycle detected for: " << c << std::endl;
      return false;
    }
    const auto it = adj.find(c);
    if (it == adj.end()) {
      std::cerr << "ERROR: not found in adj: " << c << std::endl;
      return false;
    }
    for (const auto& neibC : it->second) {
      if (!dfs(adj, visited, temp, res, neibC)) return false;
    }
    temp.erase(c);
    visited.insert(c);
    res.push_back(c);
    return true;
  }

  std::vector<char> restore(const std::vector<std::pair<char, char>>& pairs) {
    char sourceC;
    std::unordered_map<char, std::vector<char>> adj;
    if (!makeAdj(pairs, sourceC, adj)) return {};

    std::unordered_set<char> visited(adj.size());
    std::unordered_set<char> temp(adj.size());

    std::vector<char> res;
    res.reserve(adj.size());

    if (!dfs(adj, visited, temp, res, sourceC)) return {};
    std::reverse(res.begin(), res.end());
    return res;
  }
};

void test(const std::vector<std::pair<char, char>>& pairs,
          const std::string& expected) {
  Solution sol;
  std::vector<char> res = sol.restore(pairs);
  std::string resS(res.begin(), res.end());
  if (resS != expected) {
    std::cerr << "ERROR: res: " << resS << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  {
    std::vector<std::pair<char, char>> pairs;
    pairs.push_back({'a', 'c'});
    pairs.push_back({'a', 'b'});
    pairs.push_back({'a', 'c'});
    pairs.push_back({'a', 'd'});
    pairs.push_back({'b', 'c'});
    pairs.push_back({'b', 'd'});
    pairs.push_back({'c', 'd'});
    test(pairs, "abcd");
  }

  test({{'a', 'c'}, {'a', 'b'}, {'b', 'c'}}, "abc");
  test({{'a', 'c'}, {'a', 'b'}, {'b', 'c'}, {'o', 'b'}}, "");

  test({{'a', 'c'}, {'a', 'b'}, {'b', 'c'}}, "abc");
  test({{'a', 'c'}, {'a', 'b'}, {'b', 'c'}, {'c', 'a'}}, "");

  test({{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'}}, "abcde");
  test({{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'b'}, {'d', 'e'}}, "");
}
