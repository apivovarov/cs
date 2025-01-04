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
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) return head;
    ListNode* it = head;
    int sz = 0;
    ListNode* end = nullptr;
    while (it) {
      ++sz;
      end = it;
      it = it->next;
    };

    k = k % sz;
    if (k == 0) return head;

    int n = sz - k;
    it = head;
    ListNode* end2 = nullptr;
    while (n > 0) {
      --n;
      end2 = it;
      it = it->next;
    }

    ListNode* head2 = end2->next;
    end2->next = nullptr;
    end->next = head;
    return head2;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.rotateRight(n, 7);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
