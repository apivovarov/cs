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
  ListNode* n1 = new ListNode(1);
  ListNode* n2 = new ListNode(2);
  ListNode* n3 = new ListNode(3);
  ListNode* n4 = new ListNode(4);
  ListNode* n5 = new ListNode(5);
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;

  Solution sol;
  ListNode* N1 = sol.reverseList(n1);
  ListNode* N2 = N1->next;
  ListNode* N3 = N2->next;
  ListNode* N4 = N3->next;
  ListNode* N5 = N4->next;
  std::cerr << N1->val << " " << N2->val << " " << N3->val << " " << N4->val
            << " " << N5->val << std::endl;
}

