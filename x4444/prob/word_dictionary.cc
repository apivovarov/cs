#include <iostream>
#include <string>
#include <array>

class Trie {
  struct Node {
    std::array<Node*, 26> children = {};
    bool term = false;
    ~Node() {
      for (Node* ch : children) {
        if (ch) delete ch;
      }
    }
  };

  Node root{};

 public:
  void insert(std::string word) {
    Node* n = &root;
    for (char c : word) {
      if (!n->children[c - 'a']) {
        n->children[c - 'a'] = new Node();
      }
      n = n->children[c - 'a'];
    }
    n->term = true;
  }

  bool search(std::string word) { return search(word, 0, &root); }

  bool search(std::string word, int b, Node* n) {
    for (int i = b; i < word.size(); ++i) {
      char c = word[i];
      if (c == '.') {
        for (Node* ch : n->children) {
          if (!ch) continue;
          if (search(word, i + 1, ch)) return true;
        }
        return false;
      }

      if (!n->children[c - 'a']) {
        return false;
      }
      n = n->children[c - 'a'];
    }
    return n->term;
  }
};

class WordDictionary {
  Trie trie;

 public:
  void addWord(const std::string& word) { trie.insert(word); }

  bool search(const std::string& word) { return trie.search(word); }
};

int main() {
  WordDictionary t;
  t.addWord("abc");
  t.addWord("abcdef");

  std::cerr << "Search" << std::endl;
  std::cerr << std::boolalpha << t.search("abc") << std::endl;
  std::cerr << std::boolalpha << !t.search("ab") << std::endl;
  std::cerr << std::boolalpha << !t.search("ab") << std::endl;
  std::cerr << std::boolalpha << !t.search("b") << std::endl;
  std::cerr << std::boolalpha << !t.search("ba") << std::endl;
  std::cerr << std::boolalpha << !t.search("abcde") << std::endl;
  std::cerr << std::boolalpha << !t.search("abcd") << std::endl;
  std::cerr << std::boolalpha << t.search("abcdef") << std::endl;
  std::cerr << std::boolalpha << !t.search("abcdefg") << std::endl;
  std::cerr << "Search with wildcard" << std::endl;
  std::cerr << std::boolalpha << t.search("ab.") << std::endl;
  std::cerr << std::boolalpha << !t.search("ak.") << std::endl;
  std::cerr << std::boolalpha << t.search("a.c") << std::endl;
  std::cerr << std::boolalpha << !t.search("a.k") << std::endl;
  std::cerr << std::boolalpha << t.search(".bc") << std::endl;
  std::cerr << std::boolalpha << !t.search(".bk") << std::endl;
  std::cerr << std::boolalpha << t.search("a..") << std::endl;
  std::cerr << std::boolalpha << t.search(".b.") << std::endl;
  std::cerr << std::boolalpha << t.search("..c") << std::endl;
  std::cerr << std::boolalpha << !t.search("k..") << std::endl;
  std::cerr << std::boolalpha << !t.search(".k.") << std::endl;
  std::cerr << std::boolalpha << !t.search("..k") << std::endl;
  std::cerr << std::boolalpha << t.search("...") << std::endl;
}
