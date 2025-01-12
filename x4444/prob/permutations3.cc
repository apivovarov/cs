#include <iostream>
#include <utility>
#include <vector>

// 46. Permutations (Visited) - easy to understand
// Each wheel has numbers from nums - n numbers
// number of wheels is k . By default k = n
// The approach uses visited to remember what ids from nums (corresponding
// values pushed_back to stack) were already used. The approach uses recursion
// to rotate next wheel when recurs depth is n+1 (stack size == k) - append the
// result and float up
class Solution {
 public:
  void backtrack(std::vector<int>& stack, int k, std::vector<bool>& visited,
                 const std::vector<int>& nums,
                 std::vector<std::vector<int>>& res) {
    if (stack.size() == k) {
      res.push_back(stack);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (visited[i]) continue;
      visited[i] = true;
      stack.push_back(nums[i]);
      backtrack(stack, k, visited, nums, res);
      stack.pop_back();
      visited[i] = false;
    }
  }

  std::vector<std::vector<int>> permute(const std::vector<int>& nums,
                                        int k = -1) {
    if (k == -1) k = nums.size();
    std::vector<int> stack;
    std::vector<bool> visited(nums.size());
    std::vector<std::vector<int>> res;

    backtrack(stack, k, visited, nums, res);
    return res;
  }
};

// 46. Permutations (Swap) - tricky
// Uses swap approach instead of visited map. Quite tricky.
class SolutionSwap {
 public:
  void backtrack(int start, std::vector<int>& nums, int k,
                 std::vector<std::vector<int>>& res) {
    if (start == k) {
      res.push_back(std::vector(nums.begin(), nums.begin() + k));
      return;
    }

    for (int i = start; i < nums.size(); ++i) {
      std::swap(nums[start], nums[i]);
      backtrack(start + 1, nums, k, res);
      std::swap(nums[start], nums[i]);
    }
  }

  std::vector<std::vector<int>> permute(const std::vector<int>& _nums,
                                        int k = -1) {
    if (k == -1) k = _nums.size();
    std::vector<int> nums = _nums;
    std::vector<std::vector<int>> res;
    backtrack(0, nums, k, res);
    return res;
  }
};

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

int main() {
  SolutionSwap sol;
  std::cerr << sol.permute({1, 2, 3}) << std::endl;
  std::cerr << sol.permute({0, 1}) << std::endl;
  std::cerr << sol.permute({1}) << std::endl;

  std::cerr << sol.permute({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 3) << std::endl;
}
