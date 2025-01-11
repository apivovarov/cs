#include <iostream>
#include <vector>
#include <queue>
#include <string>

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

// 433. Minimum Genetic Mutation - BFS
class Solution {
  bool isOneMut(const std::string& a, const std::string& b) {
    int cnt = 0;
    for (int i = 0; i < 8; ++i) {
      if (a.at(i) != b.at(i)) ++cnt;
      if (cnt > 1) return false;
    }
    return cnt == 1;
  }

  std::vector<std::vector<int>> buildAdj(const std::vector<std::string>& bank) {
    std::vector<std::vector<int>> adj(bank.size());
    for (int i = 0; i < bank.size() - 1; ++i) {
      const std::string& a = bank[i];
      for (int j = i + 1; j < bank.size(); ++j) {
        const std::string& b = bank[j];
        if (isOneMut(a, b)) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }
    return adj;
  }

 public:
  int minMutation(const std::string& startGene, const std::string& endGene,
                  std::vector<std::string>& bank) {
    if (bank.empty()) return -1;
    if (startGene == endGene) return 0;
    
    int sid = -1;
    int eid = -1;
    for (int i = 0; i < bank.size(); ++i) {
      if (bank[i] == startGene) sid = i;
      if (bank[i] == endGene) eid = i;
      if (sid != -1 && eid != -1) break;
    }
    if (eid == -1) return -1;
    if (isOneMut(startGene, endGene)) return 1;
    if (sid == -1) {
      bank.push_back(startGene);
      sid = bank.size() - 1;
    }

    //std::cerr << sid << " " << eid << std::endl;
    //std::cerr << bank << std::endl;
    std::vector<std::vector<int>> adj = buildAdj(bank);

    // for (int i = 0; i < adj.size(); ++i) {
    //   std::cerr << i << ":" << adj[i] << std::endl;
    // }

    if (adj[eid].empty() || adj[sid].empty()) return -1;

    // BFS
    std::queue<int> qu;
    std::vector<bool> visited(bank.size());
    qu.push(sid);
    visited[sid] = true;
    int cnt = 1;
    while (!qu.empty()) {
      int qsz = qu.size();
      for (int i = 0; i < qsz; ++i) {
        int currId = qu.front();
        qu.pop();
        for (int neibId : adj[currId]) {
          if (visited[neibId]) continue;
          visited[neibId] = true;
          if (neibId == eid) return cnt;
          qu.push(neibId);
        }
      }
      ++cnt;
    }
    return -1;
  }
};

void test(std::string startGene, std::string endGene,
          const std::vector<std::string>& _bank, int expected) {
  Solution sol;
  std::vector<std::string> bank = _bank;
  int res = sol.minMutation(startGene, endGene, bank);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}, 2);
  test("AACCGGTT", "AACCGGTA", {"AACCGGTA"}, 1);
  test("AACCGGTT", "TTTTTTTT",
       {"AACCGGTA", "AACCGCTA", "AAACGGTA", "TTTTTTTT", "TTTTTTTA", "TTTTTTCA"},
       -1);
  test("CTCCTCTA", "TTTTTTTT",
       {"AACCGGTA", "AACCGCTA", "AAACGGTA", "TTTTTTTT", "TTTTTTTA", "TTTTTTBT",
        "TTTTTTCT", "CTTTTTTA", "CTTCTTTA", "CTTCTCTA"},
       5);
}
