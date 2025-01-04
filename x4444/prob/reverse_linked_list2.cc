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
  ListNode* N1 = sol.reverseBetween(n1, 2, 4);
  ListNode* N2 = N1->next;
  ListNode* N3 = N2->next;
  ListNode* N4 = N3->next;
  ListNode* N5 = N4->next;
  std::cerr << N1->val << " " << N2->val << " " << N3->val << " " << N4->val
            << " " << N5->val << std::endl;
}
