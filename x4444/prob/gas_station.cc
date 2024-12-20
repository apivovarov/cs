#include <iostream>
#include <vector>

class Solution {
 public:
  int canCompleteCircuit(const std::vector<int>& gas,
                         const std::vector<int>& cost) {
    int totalDiff = 0;
    int diff = 0;
    int start_id = 0;
    for (int i = 0; i < gas.size(); ++i) {
      diff = diff + gas[i] - cost[i];
      if (diff < 0) {
        start_id = i + 1;
        totalDiff += diff;
        diff = 0;
      }
    }
    totalDiff += diff;
    if (start_id == gas.size() || totalDiff < 0) return -1;
    return start_id;
  }
};

void test(const std::vector<int>& gas, const std::vector<int>& cost,
          int expected) {
  Solution sol;
  int res = sol.canCompleteCircuit(gas, cost);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}, 3);
  test({2, 3, 4}, {3, 4, 3}, -1);
  test({5, 1, 2, 3, 4}, {4, 4, 1, 5, 1}, 4);
  test({2}, {2}, 0);

  {
    std::vector<int> gas(100000);
    gas[99999] = 2;
    std::vector<int> cost(100000);
    cost[99998] = 1;
    test(gas, cost, 99999);
  }
  {
    std::vector<int> gas(100000);
    gas[49999] = 2;
    std::vector<int> cost(100000);
    cost[49998] = 1;
    test(gas, cost, 49999);
  }
}
