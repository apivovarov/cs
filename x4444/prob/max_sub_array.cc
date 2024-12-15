#include <iostream>
#include <vector>
#include <numeric>

class Solution {
 public:
  int maxSubArray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    if (arr.size() == 1) return arr[0];
    int sum = 0;
    int maxSum = 0;
    int maxEl = arr[0];
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];
      if (sum < 0)
        sum = 0;
      else if (sum > maxSum)
        maxSum = sum;
      if (arr[i] > maxEl) maxEl = arr[i];
    }
    if (maxSum == 0) return maxEl;
    return maxSum;
  }
};

void test(const std::vector<int>& arr, const int expected) {
  Solution sol;
  int res = sol.maxSubArray(arr);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({1}, 1);
  test({1, 2}, 3);
  test({1, 2, 1}, 4);
  test({1, 0, 1}, 2);
  test({0, 1, 1}, 2);
  test({1, 1, 0}, 2);
  test({-1, 2, -1}, 2);
  test({-1, 2}, 2);
  test({2, -1}, 2);
  test({-2, 0, -1}, 0);
  test({-2, -1, 0}, 0);
  test({0, -2, -1}, 0);
  test({-2, -1}, -1);
  test({-2, -1, -3}, -1);
  test({-1, 5, -1}, 5);
  test({1, -1, 5, -1, 1}, 5);
  test({1, -1, -1, 5, -1, -1, 1}, 5);
  test({-1, 1, 5, 1, -1}, 7);
  test({1, 2, -1, -2, 2, 1, -2, 1, 4, -5, 4}, 6);
}
