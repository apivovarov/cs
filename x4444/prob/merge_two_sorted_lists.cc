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
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode head;
    ListNode* prev = &head;
    while (l1 || l2) {
      int nV;
      if (l1 && l2) {
        if (l1->val < l2->val) {
          nV = l1->val;
          l1 = l1->next;
        } else {
          nV = l2->val;
          l2 = l2->next;
        }
      } else if (l1) {
        nV = l1->val;
        l1 = l1->next;
      } else {
        nV = l2->val;
        l2 = l2->next;
      }
      prev->next = new ListNode(nV);
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
  ListNode* resN = sol.mergeTwoLists(l1, l2);
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
  test({-1, 3, 9}, {1, 2, 3, 4}, {-1, 1, 2, 3, 3, 4, 9});
  test({-1, 2, 3, 4}, {1, 3, 9}, {-1, 1, 2, 3, 3, 4, 9});
}
