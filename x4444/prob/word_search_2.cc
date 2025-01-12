#include <iostream>
#include <vector>
#include <string>
#include <array>

class Trie {
 public:
  struct Node {
    std::array<Node*, 26> children = {};
    bool term = false;
    ~Node() {
      for (Node* ch : children) {
        if (ch) delete ch;
      }
    }
  };

 public:
  Node root{};

  void insert(const std::string& word) {
    Node* n = &root;
    for (char c : word) {
      if (!n->children[c - 'a']) {
        n->children[c - 'a'] = new Node();
      }
      n = n->children[c - 'a'];
    }
    n->term = true;
  }

  bool search(const std::string& word) {
    Node* n = &root;
    for (char c : word) {
      if (!n->children[c - 'a']) {
        return false;
      }
      n = n->children[c - 'a'];
    }
    return n->term;
  }

  bool startsWith(const std::string& prefix) {
    Node* n = &root;
    for (char c : prefix) {
      if (!n->children[c - 'a']) {
        return false;
      }
      n = n->children[c - 'a'];
    }
    return true;
  }

  bool startsWith(char c, Node*& n) {
    if (!n->children[c - 'a']) {
      return false;
    }
    n = n->children[c - 'a'];
    return true;
  }
};

// 212. Word Search II
class Solution {
 public:
  bool visit(int R, int C, const std::vector<std::vector<char>>& board,
             Trie& trie, std::vector<std::vector<bool>>& visited,
             std::string& stack, std::vector<std::string>& resWords,
             Trie::Node* tnode) {
    int rsz = board.size();
    int csz = board[0].size();
    if (R < 0 || C < 0 || R >= rsz || C >= csz || visited[R][C]) return false;
    // std::cerr << R << ":" << C << ", visited: " << std::boolalpha
    //           << visited[R][C] << " st: " << stack << std::endl;

    char c = board[R][C];
    // std::cerr << R << ":" << C << "=" << c << " st: " << stack << std::endl;
    if (!trie.startsWith(c, tnode)) {
      return false;
    }
    visited[R][C] = true;
    stack.push_back(c);
    if (tnode->term) {
      resWords.push_back(stack);
      tnode->term = false;
    }

    visit(R - 1, C, board, trie, visited, stack, resWords, tnode);
    visit(R, C - 1, board, trie, visited, stack, resWords, tnode);
    visit(R + 1, C, board, trie, visited, stack, resWords, tnode);
    visit(R, C + 1, board, trie, visited, stack, resWords, tnode);

    stack.pop_back();
    visited[R][C] = false;
    return false;
  }

  std::vector<std::string> findWords(
      const std::vector<std::vector<char>>& board,
      const std::vector<std::string>& words) {
    Trie trie;
    for (const std::string& w : words) {
      trie.insert(w);
    }

    int rsz = board.size();
    int csz = board[0].size();

    std::vector<std::string> resWords;
    std::vector<std::vector<bool>> visited(rsz, std::vector<bool>(csz, false));
    std::string stack = "";

    for (int r = 0; r < rsz; ++r) {
      for (int c = 0; c < csz; ++c) {
        visit(r, c, board, trie, visited, stack, resWords, &trie.root);
      }
    }
    return resWords;
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

void test(const std::vector<std::vector<char>>& board,
          const std::vector<std::string>& words,
          const std::vector<std::string>& expected) {
  Solution sol;
  std::vector<std::string> res = sol.findWords(board, words);
  std::sort(res.begin(), res.end());
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test({{'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}},
       {"oath", "pea", "eat", "rain"}, {"eat", "oath"});

  test({{'a', 'b'}, {'c', 'd'}}, {"abcb"}, {});

  test({{'o', 'a', 'b', 'n'},
        {'o', 't', 'a', 'e'},
        {'a', 'h', 'k', 'r'},
        {'a', 'f', 'l', 'v'}},
       {"oa", "oaa"}, {"oa", "oaa"});

  test({{'a', 'b', 'c', 'e'}, {'x', 'x', 'c', 'd'}, {'x', 'x', 'b', 'a'}},
       {"abc", "abcd"}, {"abc", "abcd"});
}
