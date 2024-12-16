#include <iostream>
#include <vector>

class Solution {
 public:
  int hIndex(std::vector<int>& citations) {
    if (citations.empty()) return 0;
    std::sort(citations.rbegin(), citations.rend());
    for (int i = 0; i < citations.size(); ++i) {
      if (i + 1 > citations[i]) return i;
    }
    return citations.size();
  }
};

void test(std::vector<int> arr, int expected) {
  Solution sol;
  int res = sol.hIndex(arr);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1, 3, 1}, 1);
  test({3, 0, 6, 1, 5}, 3);
  test({100}, 1);
  test({3, 5}, 2);
  test({4, 4, 0, 0}, 2);
}
