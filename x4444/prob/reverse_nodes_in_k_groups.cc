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
  // b   e | b   e | b   e
  // 3 2 1 | 6 5 4 | 9 8 7 | 10 11
  // p0  p1  p0  p1  p0  p1
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || !head->next || k < 2) return head;
    ListNode* head2 = nullptr;
    ListNode* p0 = nullptr;
    ListNode* prev_end = nullptr;
    ListNode* end = head;
    int cnt = 0;
    ListNode* curn = head;
    while (curn) {
      ListNode* p1 = curn->next;
      curn->next = p0;
      p0 = curn;
      curn = p1;
      ++cnt;
      if (cnt == k) {
        if (!head2) head2 = p0;
        if (prev_end) prev_end->next = p0;
        prev_end = end;
        end = p1;
        p0 = nullptr;
        cnt = 0;
      }
    }
    if (cnt != k) {
      curn = p0;
      p0 = nullptr;
      while (curn) {
        ListNode* p1 = curn->next;
        curn->next = p0;
        p0 = curn;
        curn = p1;
      }
      prev_end->next = p0;
    }
    return head2;
  }
};

int main() {
  ListNode* n = nullptr;
  for (int i = 11; i >= 1; --i) {
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.reverseKGroup(n, 4);
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}
