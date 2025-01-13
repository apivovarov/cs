#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 148. Sort List - Merge Sort - O(1) memory
class Solution {
 public:
  ListNode* mergeSort(ListNode* head, ListNode* end) {
    if (head == end) return nullptr;
    if (head->next == end) {
      head->next = nullptr;
      return head;
    }
    ListNode* mid = head;
    ListNode* fast = head;
    while (fast != end && fast->next != end) {
      mid = mid->next;
      fast = fast->next->next;
    }

    ListNode* p1 = mergeSort(head, mid);
    ListNode* p2 = mergeSort(mid, end);

    ListNode dummy;
    ListNode* prev = &dummy;
    while (p1 && p2) {
      if (p1->val < p2->val) {
        prev->next = p1;
        p1 = p1->next;
      } else {
        prev->next = p2;
        p2 = p2->next;
      }
      prev = prev->next;
    }
    prev->next = p1 ? p1 : p2;  // attach remaining list
    return dummy.next;
  }

  ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    return mergeSort(head, nullptr);
  }
};

void delList(ListNode* n) {
  while (n) {
    ListNode* tmp = n->next;
    delete n;
    n = tmp;
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void test(const std::vector<int>& inp, const std::vector<int>& expected) {
  ListNode dummy;
  ListNode* prev = &dummy;
  for (int i = 0; i < inp.size(); ++i) {
    prev->next = new ListNode(inp[i]);
    prev = prev->next;
  }

  Solution sol;
  ListNode* res = sol.sortList(dummy.next);
  std::vector<int> resV;
  while (res) {
    resV.push_back(res->val);
    res = res->next;
  }
  if (resV != expected) {
    std::cerr << "ERROR: res: " << resV << std::endl;
  }
  delList(res);
  delList(dummy.next);
  dummy.next = nullptr;
}

int main() {
  test({}, {});
  test({5}, {5});
  test({5, 2}, {2, 5});
  test({1, 5, 2}, {1, 2, 5});
  test({4, 2, 1, 3}, {1, 2, 3, 4});
  test({-1, 5, 3, 4, 0}, {-1, 0, 3, 4, 5});
}
