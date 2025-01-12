#include <iostream>
#include <string>
#include <vector>

// 77. Combinations
class Solution {
 public:
  void backtrack(int n, int k, int start, std::vector<int>& stack,
                 std::vector<std::vector<int>>& res) {
    int pos = stack.size();
    if (pos == k) {
      res.push_back(stack);
      return;
    }

    for (int i = start; i <= n - (k - (pos + 1)); ++i) {
      stack.push_back(i);
      backtrack(n, k, i + 1, stack, res);
      stack.pop_back();
    }
  }

  std::vector<std::vector<int>> combine(int n, int k) {
    std::vector<int> stack;
    std::vector<std::vector<int>> res;

    backtrack(n, k, 1, stack, res);
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

void test(int n, int k, const std::vector<std::vector<int>>& expected) {
  Solution sol;
  std::vector<std::vector<int>> res = sol.combine(n, k);
  std::sort(res.begin(), res.end());

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test(4, 2, {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}});
  test(4, 3, {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}});
  test(1, 1, {{1}});
  test(4, 1, {{1}, {2}, {3}, {4}});
}
