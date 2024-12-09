#include <vector>

class Solution {
 public:
  int majorityElement(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() <= 2) return nums[0];

    int maj_el0;
    int maj_freq0 = 0;
    int maj_el1;
    int maj_freq1 = 0;
    int cur_freq = 1;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1]) {
        ++cur_freq;
      } else {
        if (maj_freq0 == 0 || nums[i - 1] == maj_el0) {
          maj_freq0 += cur_freq;
          maj_el0 = nums[i - 1];
        } else if (maj_freq1 == 0 || nums[i - 1] == maj_el1) {
          maj_freq1 += cur_freq;
          maj_el1 = nums[i - 1];
        } else if (cur_freq > maj_freq0) {
          maj_freq0 = cur_freq;
          maj_el0 = nums[i - 1];
        } else if (cur_freq > maj_freq1) {
          maj_freq1 = cur_freq;
          maj_el1 = nums[i - 1];
        }
        cur_freq = 1;
      }
    }
    int i = nums.size();
    if (maj_freq0 == 0 || nums[i - 1] == maj_el0) {
      maj_freq0 += cur_freq;
      maj_el0 = nums[i - 1];
    } else if (maj_freq1 == 0 || nums[i - 1] == maj_el1) {
      maj_freq1 += cur_freq;
      maj_el1 = nums[i - 1];
    } else if (cur_freq > maj_freq0) {
      maj_freq0 = cur_freq;
      maj_el0 = nums[i - 1];
    } else if (cur_freq > maj_freq1) {
      maj_freq1 = cur_freq;
      maj_el1 = nums[i - 1];
    }

    return (maj_freq0 > maj_freq1) ? maj_el0 : maj_el1;
  }
};

void test(std::vector<int> arr, int expected) {
  Solution sol;
  int res = sol.majorityElement(arr);
  if (res != expected) throw std::runtime_error("Bad result");
}

int main() {
  test({}, 0);
  test({4}, 4);
  test({4, 4}, 4);
  test({4, 5, 4}, 4);
  test({4, 4, 4, 5, 5, 5, 5}, 5);
  test({6, 4, 4, 6, 4, 5, 5, 6, 6, 5, 6, 6, 6}, 6);
  test({4, 5, 5, 4, 5}, 5);
  test({5, 4, 5, 4, 5}, 5);
  test({5, 5, 4, 5, 4, 4, 4, 4, 4, 5, 5, 5, 3, 3, 3, 5, 5, 3, 5, 5, 5, 3, 5},
       5);
  test({5, 5, 5, 1, 1, 4, 4, 4, 5, 4, 4, 4, 5,
        5, 5, 3, 3, 5, 5, 3, 5, 5, 5, 3, 5},
       5);
}