#include <iostream>
#include <vector>

class Solution {
 public:
  int trap(const std::vector<int>& height) {
    if (height.size() < 3) return 0;
    int lp = 0;
    int rp = height.size() - 1;
    int lh = height[lp];
    int rh = height[rp];
    int sum = 0;
    int curh = 0;
    while (true) {
      if (lh <= rh) {
        ++lp;
        if (lp >= rp) break;
        curh = height[lp];
        if (curh >= lh) {
          lh = curh;
          continue;
        }
      } else {
        --rp;
        if (lp >= rp) break;
        curh = height[rp];
        if (curh >= rh) {
          rh = curh;
          continue;
        }
      }
      sum += (std::min(lh, rh) - curh);
    }
    return sum;
  }
};

void test(const std::vector<int>& height, int expected) {
  Solution sol;
  int res = sol.trap(height);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1}, 0);
  test({1, 0}, 0);
  test({1, 1, 1}, 0);
  test({1, 1, 1, 1}, 0);
  test({1, 2, 3, 4}, 0);
  test({4, 3, 2, 1}, 0);
  test({1, 2, 2, 1}, 0);
  test({2, 1, 1, 2}, 2);
  test({3, 0, 1, 2}, 3);
  test({2, 0, 1, 3}, 3);
  test({4, 0, 2, 0, 4}, 10);
  test({2, 0, 1, 3, 4, 0, 2, 0, 4}, 13);
  test({2, 0, 1, 3, 4, 0, 2, 0, 4, 2, 1, 1, 2}, 15);
  test({4, 0, 2, 0, 5}, 10);
  test({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6);
  test({4, 2, 0, 3, 2, 5}, 9);
}
