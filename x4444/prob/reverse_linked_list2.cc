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
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (!head || !head->next || left >= right) return head;
    ListNode root;
    ListNode* prev = &root;
    ListNode* old_prev = &root;
    ListNode* next = nullptr;
    int pos = 1;
    while (head) {
      if (pos >= left && pos <= right) {
        next = new ListNode(head->val, next);
        if (pos == left) {
          old_prev = prev;
          prev = next;
        } else if (pos == right) {
          old_prev->next = next;
        }
      } else {
        prev->next = new ListNode(head->val);
        prev = prev->next;
      }
      head = head->next;
      ++pos;
    }
    return root.next;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.reverseBetween(n, 2, 4);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
