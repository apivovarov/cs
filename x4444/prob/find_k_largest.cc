#include <iostream>
#include <vector>
#include <queue>

// 215. Kth Largest Element in an Array
class Solution {
 public:
  int findKthLargest(const std::vector<int>& nums, int k) {
    if (nums.size() == 1 && k == 1) return nums[0];
    std::priority_queue<int> pq(nums.begin(), nums.end());
    for (int i = 1; i < k; ++i) {
      pq.pop();
    }
    return pq.top();
  }
};

int main() {
  Solution sol;
  std::cerr << sol.findKthLargest({3}, 1) << std::endl;
  std::cerr << sol.findKthLargest({3, 2, 1, 5, 6, 4}, 2) << std::endl;
  std::cerr << sol.findKthLargest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4) << std::endl;
}
