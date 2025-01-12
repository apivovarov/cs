#include <iostream>
#include <vector>

// 39. Combination Sum
class Solution {
 public:
  void backtrack(int pos, const std::vector<int>& candidates, int target,
                 std::vector<int>& stack, int sum,
                 std::vector<std::vector<int>>& res) {
    if (sum == target) {
      res.push_back(stack);
      return;
    }
    if (sum > target) {
      return;
    }
    for (int i = pos; i < candidates.size(); ++i) {
      stack.push_back(candidates[i]);
      backtrack(i, candidates, target, stack, sum + candidates[i], res);
      stack.pop_back();
    }
  }

  std::vector<std::vector<int>> combinationSum(
      const std::vector<int>& candidates, int target) {
    std::vector<int> stack;
    std::vector<std::vector<int>> res;

    backtrack(0, candidates, target, stack, 0, res);
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

void test(const std::vector<int>& candidates, int target,
          const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = sol.combinationSum(candidates, target);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test({2}, 1, {});
  test({2, 3, 5}, 8, {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}});
  test({3, 2, 5}, 8, {{3, 3, 2}, {3, 5}, {2, 2, 2, 2}});
  test({2, 3, 6, 7}, 7, {{2, 2, 3}, {7}});
}
