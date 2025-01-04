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
    ListNode root;
    root.next = head;
    ListNode* prevprev = &root;
    ListNode* prev = head;
    ListNode* it = head->next;
    bool wasdel = false;
    while (it) {
      if (it->val == prev->val) {
        prev->next = it->next;
        ListNode* tmp = it;
        it = it->next;
        delete tmp;
        wasdel = true;
      } else {
        if (wasdel) {
          prevprev->next = it;
          ListNode* tmp = prev;
          prev = prevprev;
          delete tmp;
          wasdel = false;
        }
        prevprev = prev;
        prev = it;
        it = it->next;
      }
    }
    if (wasdel) {
      prevprev->next = nullptr;
      ListNode* tmp = prev;
      delete tmp;
    }
    return root.next;
  }
};

void test1() {
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

void test2() {
  ListNode* n = nullptr;
  int cnt1 = 2;
  int cnt4 = 3;
  int cnt5 = 3;
  for (int i = 5; i >= 1; --i) {
    n = new ListNode(i, n);
    if (i == 1 && cnt1 > 1) {
      --cnt1;
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

void test3() {
  ListNode* n = nullptr;
  for (int i = 3; i >= 1; --i) {
    n = new ListNode(i, n);
    n = new ListNode(i, n);
  }

  Solution sol;
  ListNode* N1 = sol.deleteDuplicates(n);
  if (!N1) std::cerr << "Empty";
  while (N1) {
    std::cerr << N1->val << " ";
    N1 = N1->next;
  }
  std::cerr << std::endl;
}

int main() {
  test1();
  test2();
  test3();
}
