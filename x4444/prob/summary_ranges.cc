#include <iostream>
#include <string>
#include <vector>

class Solution {
 public:
  std::vector<std::string> summaryRanges(const std::vector<int>& nums) {
    if (nums.empty()) return {};
    if (nums.size() == 1) return {std::to_string(nums[0])};

    std::vector<std::string> res;
    int b = nums[0];
    int e = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1] + 1) {
        e = nums[i];
        continue;
      }
      if (b == e) {
        // dump simple
        res.push_back(std::to_string(b));
      } else {
        // dump range
        res.push_back(std::to_string(b).append("->").append(std::to_string(e)));
      }
      b = nums[i];
      e = nums[i];
    }
    if (b == e) {
      // dump simple
      res.push_back(std::to_string(b));
    } else {
      // dump range
      res.push_back(std::to_string(b).append("->").append(std::to_string(e)));
    }
    return res;
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void test(const std::vector<int>& nums,
          const std::vector<std::string>& expected) {
  Solution sol;
  std::vector<std::string> res = sol.summaryRanges(nums);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() { 
    test({}, {}); 
    test({4}, {"4"}); 
    test({0, 1, 2, 4, 5, 7}, {"0->2", "4->5", "7"}); 
    test({0, 1, 2, 4, 7, 8}, {"0->2", "4", "7->8"}); 
    }
