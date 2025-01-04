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
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* it = head;
    ListNode* prev = it;
    it = it->next;
    while (it) {
      if (it->val == prev->val) {
        prev->next = it->next;
        ListNode* tmp = it;
        it = it->next;
        delete tmp;
      } else {
        prev = it;
        it = it->next;
      }
    }
    return head;
  }
};

int main() {
  ListNode* n = nullptr;
  int cnt3 = 2;
  int cnt4 = 3;
  int cnt5 = 3;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
    if (i == 3 && cnt3 > 1) {
      --cnt3;
      ++i;
    } else if (i == 4 && cnt4 > 1) {
      --cnt4;
      ++i;
    } else if (i == 5 && cnt5 > 1) {
      --cnt5;
      ++i;
    }
  }

  Solution sol;
  ListNode* N1 = sol.deleteDuplicates(n);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
