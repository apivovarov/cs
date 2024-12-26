#include <iostream>
#include <vector>

class Solution {
 public:
  int maxArea(const std::vector<int>& height) {
    if (height.size() < 2) return 0;

    int maxSum = 0;
    int b = 0;
    int e = height.size() - 1;

    while (b < e) {
      int minH = std::min(height[b], height[e]);
      int sum = minH * (e - b);
      if (sum > maxSum) {
        maxSum = sum;
      }
      if (height[e] < height[b]) {
        --e;
      } else {
        ++b;
      }
    }
    return maxSum;
  }
};

void test(const std::vector<int>& height, int expected) {
  Solution sol;
  int res = sol.maxArea(height);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1, 8}, 1);
  test({8, 1}, 1);
  test({5, 8}, 5);
  test({8, 5}, 5);
  test({1, 1, 1}, 2);
  test({4, 1, 5}, 8);
  test({4, 1, 5, 2}, 8);
  test({2, 5, 1, 4, 2}, 8);
  test({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49);
}
