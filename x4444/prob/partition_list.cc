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
  ListNode* partition(ListNode* head, int x) {
    if (!head || !head->next) return head;
    ListNode small;
    ListNode large;
    ListNode* se = &small;
    ListNode* le = &large;

    auto it = head;
    while (it) {
      if (it->val < x) {
        se->next = it;
        se = it;
      } else {
        le->next = it;
        le = it;
      }
      it = it->next;
    }
    le->next = nullptr;
    se->next = large.next;
    return small.next;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 1; i <= 5; ++i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.partition(n, 2);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
