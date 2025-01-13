#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

static int cnt = 0;

static ListNode* merge(ListNode* a, ListNode* b) {
  if (!a && !b) return nullptr;
  if (!a) return b;
  if (!b) return a;
  ListNode dummy;
  ListNode* tail = &dummy;
  while (a && b) {
    if (a->val < b->val) {
      tail->next = a;
      a = a->next;
    } else {
      tail->next = b;
      b = b->next;
    }
    ++cnt;
    tail = tail->next;
  }
  tail->next = a ? a : b;
  return dummy.next;
}

// 23. Merge k Sorted Lists - Divide-and-Conquer Approach - fastest
class Solution {
 public:
  ListNode* mergeRecur(int b, int e, std::vector<ListNode*>& lists) {
    if (b >= e) return nullptr;
    if (e - b == 1) return lists[b];
    if (e - b == 2) return merge(lists[b], lists[b + 1]);
    int m = b + (e - b) / 2;
    return merge(mergeRecur(b, m, lists), mergeRecur(m, e, lists));
  }

  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    return mergeRecur(0, lists.size(), lists);
  }
};

// Iterative Merging one-by-one to/with final list - slower
class Solution2 {
 public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    if (lists.size() == 1) return lists[0];
    ListNode* a = lists.back();
    lists.pop_back();
    while (!lists.empty()) {
      ListNode* b = lists.back();
      lists.pop_back();
      ListNode* merged = merge(a, b);
      a = merged;
    }
    return a;
  }
};

std::ostream& operator<<(std::ostream& os, std::vector<int> vv) {
  for (int v : vv) std::cerr << v << ",";
  return os;
}

void test(const std::vector<std::vector<int>>& lists,
          const std::vector<int>& expc) {
  std::vector<ListNode*> listsN;

  for (const std::vector<int>& n1 : lists) {
    ListNode* l1 = nullptr;
    for (auto it = n1.rbegin(); it != n1.rend(); ++it) {
      l1 = new ListNode(*it, l1);
    }
    listsN.push_back(l1);
  }

  Solution sol;
  ListNode* resN = sol.mergeKLists(listsN);
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
  test({{1, 3}}, {1, 3});
  test({{1, 3, 8}, {4, 5}}, {1, 3, 4, 5, 8});
  test({{1, 3, 8}, {4, 5}, {3}, {}, {-5, 7}}, {-5, 1, 3, 3, 4, 5, 7, 8});
  test({{}, {}}, {});
  test({{1, 3}, {}}, {1, 3});
  test({{}, {4, 5}}, {4, 5});
  test({{-1, 3, 9}, {1, 2, 3, 4}}, {-1, 1, 2, 3, 3, 4, 9});
  test({{-1, 2, 3, 4}, {1, 3, 9}}, {-1, 1, 2, 3, 3, 4, 9});
  test({{-1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
         3,  3,  3,  3,  3,  3,  3,  3,  9,  9, 9, 9, 9, 9, 9, 9, 9, 9},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
         3,  3,  3,  3,  3,  3,  3,  3,  9,  9, 9, 9, 9, 9, 9, 9, 9, 9},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
         3,  3,  3,  3,  3,  3,  3,  3,  9,  9, 9, 9, 9, 9, 9, 9, 9, 9},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
         3,  3,  3,  3,  3,  3,  3,  3,  9,  9, 9, 9, 9, 9, 9, 9, 9, 9}},
       {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
        9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
        9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9});

  std::cerr << "steps: " << cnt << std::endl;
}
