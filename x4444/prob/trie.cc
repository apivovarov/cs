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
};

int main() {
  Trie t;
  t.insert("abc");
  t.insert("abcdef");
  std::cerr << "StartsWith" << std::endl;
  std::cerr << std::boolalpha << t.startsWith("a") << std::endl;
  std::cerr << std::boolalpha << t.startsWith("ab") << std::endl;
  std::cerr << std::boolalpha << t.startsWith("abc") << std::endl;
  std::cerr << std::boolalpha << t.startsWith("abcd") << std::endl;
  std::cerr << std::boolalpha << !t.startsWith("abcm") << std::endl;
  std::cerr << std::boolalpha << !t.startsWith("b") << std::endl;
  std::cerr << std::boolalpha << !t.startsWith("ba") << std::endl;

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
}
