#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (!head || n == 0) return head;
    auto it = head;
    int sz = 0;
    while (it) {
      ++sz;
      it = it->next;
    }
    ListNode root(0, head);
    it = &root;
    int k = sz - n;
    while (k > 0) {
      --k;
      it = it->next;
    }
    auto tmp = it->next;
    it->next = tmp->next;
    delete tmp;
    return root.next;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.removeNthFromEnd(n, 2);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
