#include <iostream>
#include <vector>

// 918. Maximum Sum Circular Subarray
class Solution {
 public:
  int maxSubArray(const std::vector<int>& arr) {
    int sum = 0;
    int maxSum = -1e6;
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];
      if (sum > maxSum) maxSum = sum;
      if (sum < 0) sum = 0;
    }
    return maxSum;
  }

  int minSubArray(const std::vector<int>& arr) {
    int sum = 0;
    int minSum = 1e6;
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];
      if (sum < minSum) minSum = sum;
      if (sum > 0) sum = 0;
    }
    return minSum;
  }

  int maxSubarraySumCircular(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    int n = arr.size();
    if (n == 1) return arr[0];

    int maxSubArrSum2 = 0;
    int max = -1e6;
    // base case
    for (int i = 0; i < arr.size(); ++i) {
      maxSubArrSum2 += arr[i];  // Total sum
      if (arr[i] > max) max = arr[i];
    }
    // all negative case
    if (max <= 0) return max;

    // total sum is min-sub-array + max-sub-array.
    // One of the sub arrays is entirely contained within the array
    // lets calulate max-sub-array using two approaches and select the best
    maxSubArrSum2 -= minSubArray(arr);  // alternative maxSubArrSum
    int maxSubArrSum = maxSubArray(arr);
    return maxSubArrSum > maxSubArrSum2 ? maxSubArrSum : maxSubArrSum2;
  }
};

void test(const std::vector<int>& arr, const int expected) {
  Solution sol;
  int res = sol.maxSubarraySumCircular(arr);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({}, 0);
  test({1}, 1);
  test({1, 2}, 3);
  test({1, -2, 3, -2}, 3);
  test({6, -8, 2, 1, 1, 1, -4, 2, 1, 1}, 11);
  test({2, 1, 1, 6, -8, 2, 1, 1, 1, -4}, 11);
  test({1, 1, -4, 2, 1, 1, 6, -8, 2, 1}, 11);
  test({2, 1, 1, 1, -4, 2, 1, 1, 6, -8}, 11);
  test({-8, 2, 1, 1, 1, -4, 2, 1, 1, 6}, 11);
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
  test({1, -1, 5, -1, 1}, 6);
  test({1, -1, -1, 5, -1, -1, 1}, 5);
  test({-1, 1, 5, 1, -1}, 7);
  test({1, 2, -1, -2, 2, 1, -2, 1, 4, -5, 4}, 10);
}
