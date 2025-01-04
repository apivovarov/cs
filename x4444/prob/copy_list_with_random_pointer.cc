#include <iostream>
#include <unordered_map>

class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = nullptr;
    random = nullptr;
  }
};

class Solution {
 public:
  Node* copyRandomList(Node* head) {
    if (!head) return head;
    std::unordered_map<Node*, Node*> map;
    Node root(0);
    Node* prev = &root;

    Node* it = head;
    while (it) {
      Node* n = new Node(it->val);
      map.emplace(it, n);
      n->random = it->random;
      prev->next = n;
      prev = prev->next;
      it = it->next;
    }

    it = root.next;
    while (it) {
      if (it->random) {
        it->random = map.at(it->random);
      }
      it = it->next;
    }
    return root.next;
  }
};

void check(Node* a, Node* b, std::string tag = "") {
  if (a != b) std::cerr << "ERROR: a!=b, tag: " << tag << std::endl;
}

int main() {
  Solution sol;

  Node* n1 = new Node(1);
  Node* n10 = new Node(10);
  Node* n11 = new Node(11);
  Node* n13 = new Node(13);
  Node* n7 = new Node(7);
  n7->next = n13;
  n7->random = nullptr;
  n13->next = n11;
  n13->random = n7;
  n11->next = n10;
  n11->random = n1;
  n10->next = n1;
  n10->random = n11;
  n1->next = nullptr;
  n1->random = n7;

  Node* N7 = sol.copyRandomList(n7);
  Node* N13 = N7->next;
  Node* N11 = N13->next;
  Node* N10 = N11->next;
  Node* N1 = N10->next;
  Node* E = N1->next;

  check(E, nullptr, "E");
  check(N7->random, nullptr, "N7");
  check(N13->random, N7, "N13");
  check(N11->random, N1, "N11");
  check(N10->random, N11, "N10");
  check(N1->random, N7, "N1");

  check(sol.copyRandomList(nullptr), nullptr, "Empty");
}
