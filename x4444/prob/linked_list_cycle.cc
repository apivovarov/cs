#include <iostream>

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    if (head == nullptr) return false;
    ListNode *fast = head->next;
    ListNode *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
      if (fast == slow) return true;
      slow = slow->next;
      fast = fast->next->next;
    }
    return false;
  }
};

void test(ListNode *n, bool expected, const std::string &id) {
  Solution sol;
  bool res = sol.hasCycle(n);
  if (res != expected) {
    std::cerr << "ERROR: for id: " << id << std::endl;
  }
}

int main() {
  {
    ListNode a(-4);
    ListNode b(0);
    b.next = &a;
    ListNode c(2);
    c.next = &b;
    ListNode d(3);
    d.next = &c;
    a.next = &c;
    test(&d, true, "1");
  }
  {
    ListNode a(-4);
    test(&a, false, "2");
  }
  {
    ListNode a(-4);
    a.next = &a;
    test(&a, true, "3");
  }
  {
    ListNode a(-4);
    ListNode b(0);
    b.next = &a;
    ListNode c(2);
    c.next = &b;
    ListNode d(3);
    d.next = &c;
    test(&d, false, "4");
  }
}
