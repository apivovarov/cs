#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

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

// 127. Word Ladder - BFS - wildcard to build adj - fastest
class Solution {
  std::unordered_map<std::string, std::vector<int>> wildcard(
      const std::vector<std::string>& wordList) {
    std::unordered_map<std::string, std::vector<int>> wild;
    for (int i = 0; i < wordList.size(); ++i) {
      const std::string& w = wordList[i];
      for (int j = 0; j < w.size(); ++j) {
        std::string w2 = w;
        w2[j] = '*';
        wild[w2].push_back(i);
      }
    }
    return wild;
  }

  bool isOneDiff(const std::string& a, const std::string& b) {
    int N = a.size();
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
      if (a.at(i) != b.at(i)) ++cnt;
      if (cnt > 1) return false;
    }
    return cnt == 1;
  }

  std::vector<std::vector<int>> buildAdj(
      const std::vector<std::string>& wordList) {
    std::unordered_map<std::string, std::vector<int>> wild = wildcard(wordList);

    int N = wordList.size();
    std::vector<std::vector<int>> adj(N);
    for (const auto& pa : wild) {
      const std::vector<int>& neib = pa.second;
      for (int v : neib) {
        for (int v2 : neib) {
          if (v == v2) continue;
          adj[v].push_back(v2);
        }
      }
    }
    return adj;
  }

 public:
  int ladderLength(const std::string& beginWord, const std::string& endWord,
                   std::vector<std::string>& wordList) {
    if (beginWord == endWord) return 1;
    if (wordList.empty()) return 0;

    int bid = -1;
    int eid = -1;

    for (int i = 0; i < wordList.size(); ++i) {
      if (wordList[i] == beginWord)
        bid = i;
      else if (wordList[i] == endWord)
        eid = i;
      if (bid != -1 && eid != -1) break;
    }
    if (eid == -1) return 0;
    if (bid == -1) {
      wordList.push_back(beginWord);
      bid = wordList.size() - 1;
    }

    if (isOneDiff(beginWord, endWord)) return 2;

    std::vector<std::vector<int>> adj = buildAdj(wordList);
    if (adj[bid].empty() || adj[eid].empty()) return 0;

    // BFS
    std::queue<int> qu;
    qu.push(bid);
    std::vector<bool> visited(adj.size());
    visited[bid] = true;
    int cnt = 1;  // number of transformations
    while (!qu.empty()) {
      int qsz = qu.size();
      for (int i = 0; i < qsz; ++i) {
        int nid = qu.front();
        qu.pop();
        // std::cerr << "  W: " << w << " , cnt: " << cnt << std::endl;
        for (int neibId : adj[nid]) {
          if (visited[neibId]) continue;
          // std::cerr << "    neibW: " << neibW << std::endl;
          if (neibId == eid) return cnt + 1;
          qu.push(neibId);
          visited[neibId] = true;
        }
      }
      ++cnt;
    }
    return 0;
  }
};

// BFS - without adjacent list - slow.
class SolutionShort {
  bool isOneDiff(const std::string& a, const std::string& b) {
    int N = a.size();
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
      if (a.at(i) != b.at(i)) ++cnt;
      if (cnt > 1) return false;
    }
    return cnt == 1;
  }

 public:
  int ladderLength(const std::string& beginWord, const std::string& endWord,
                   const std::vector<std::string>& wordList) {
    if (beginWord == endWord) return 1;
    if (wordList.empty()) return 0;
    if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end())
      return 0;
    if (isOneDiff(beginWord, endWord)) return 2;

    // BFS
    std::queue<std::string> qu;
    qu.push(beginWord);
    std::unordered_set<std::string> visited;
    visited.insert(beginWord);
    int cnt = 1;  // number of transformations
    while (!qu.empty()) {
      int qsz = qu.size();
      for (int i = 0; i < qsz; ++i) {
        std::string w = qu.front();
        qu.pop();
        // std::cerr << "  W: " << w << " , cnt: " << cnt << std::endl;
        for (const std::string& neibW : wordList) {
          if (visited.count(neibW) > 0) continue;
          if (isOneDiff(w, neibW)) {
            // std::cerr << "    neibW: " << neibW << std::endl;
            if (neibW == endWord) return cnt + 1;
            qu.push(neibW);
            visited.insert(neibW);
          }
        }
      }
      ++cnt;
    }
    return 0;
  }
};

void test(std::string beginWord, std::string endWord,
          const std::vector<std::string>& _wordList, int expected) {
  Solution sol;
  std::vector<std::string> wordList = _wordList;
  int res = sol.ladderLength(beginWord, endWord, wordList);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}, 5);
  test("hit", "aaa", {"hot", "dot", "dog", "lot", "log", "cog"}, 0);
  test("hit", "aaa", {}, 0);
  test("hit", "hit", {}, 1);
  test("AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}, 3);
  test("AACCGGTT", "AACCGGTA", {"AACCGGTA"}, 2);
  test("AACCGGTT", "TTTTTTTT",
       {"AACCGGTA", "AACCGCTA", "AAACGGTA", "TTTTTTTT", "TTTTTTTA", "TTTTTTCA"},
       0);
  test("CTCCTCTA", "TTTTTTTT",
       {"AACCGGTA", "AACCGCTA", "AAACGGTA", "TTTTTTTT", "TTTTTTTA", "TTTTTTBT",
        "TTTTTTCT", "CTTTTTTA", "CTTCTTTA", "CTTCTCTA"},
       6);
}
