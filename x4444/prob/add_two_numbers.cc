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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr && l2 == nullptr) return l1;
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode head;
    ListNode* prev = &head;
    int carry = 0;
    while (l1 || l2) {
      int v1 = l1 == nullptr ? 0 : l1->val;
      int v2 = l2 == nullptr ? 0 : l2->val;
      int resV = v1 + v2 + carry;
      carry = 0;
      if (resV > 9) {
        carry = 1;
        resV %= 10;
      }
      prev->next = new ListNode(resV);
      prev = prev->next;
      if (l1) l1 = l1->next;
      if (l2) l2 = l2->next;
    }
    if (carry > 0) {
      prev->next = new ListNode(1);
      prev = prev->next;
    }
    return head.next;
  }
};

std::ostream& operator<<(std::ostream& os, std::vector<int> vv) {
  for (int v : vv) std::cerr << v << ",";
  return os;
}

void test(const std::vector<int>& n1, const std::vector<int>& n2,
          const std::vector<int>& expc) {
  ListNode* l1 = nullptr;
  ListNode* l2 = nullptr;
  for (auto it = n1.rbegin(); it != n1.rend(); ++it) {
    l1 = new ListNode(*it, l1);
  }
  for (auto it = n2.rbegin(); it != n2.rend(); ++it) {
    l2 = new ListNode(*it, l2);
  }

  Solution sol;
  ListNode* resN = sol.addTwoNumbers(l1, l2);
  std::vector<int> res;
  while (resN) {
    res.push_back(resN->val);
    resN = resN->next;
  }
  if (res != expc) {
    std::cerr << "ERROR: res: " << res << ", expc: " << expc << std::endl;
  }
}

int main() {
  test({}, {}, {});
  test({1, 3}, {}, {1, 3});
  test({}, {4, 5}, {4, 5});
  test({2, 4, 3}, {5, 6, 4}, {7, 0, 8});
  test({2, 4, 3}, {5, 6}, {7, 0, 4});
  test({2, 4, 3}, {5}, {7, 4, 3});
  test({2, 4}, {5, 6, 4}, {7, 0, 5});
  test({9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}, {8, 9, 9, 9, 0, 0, 0, 1});
}
