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
  ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* next = nullptr;
    while (head) {
      next = new ListNode(head->val, next);
      head = head->next;
    }
    return next;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.reverseList(n);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
