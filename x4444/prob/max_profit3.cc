#include <iostream>
#include <vector>

// 123. Best Time to Buy and Sell Stock III
class Solution {
 public:
  int maxProfit(const std::vector<int>& prices) {
    int sz = prices.size();
    if (sz == 0) return 0;
    if (sz == 1) return 0;
    if (sz == 2) return std::max(0, prices[1] - prices[0]);

    // Max Profit from begin to day i.
    std::vector<int> lProf(sz);
    lProf[0] = 0;
    int minP = prices[0];
    for (int i = 1; i < sz; ++i) {
      lProf[i] = std::max(prices[i] - minP, lProf[i - 1]);
      minP = std::min(minP, prices[i]);
    }

    // Max Profit from day i to end
    std::vector<int> rProf(sz);
    rProf[sz - 1] = 0;
    int maxP = prices[sz - 1];
    for (int _i = sz - 1; _i > 0; --_i) {
      int i = _i - 1;
      rProf[i] = std::max(maxP - prices[i], rProf[i + 1]);
      maxP = std::max(maxP, prices[i]);
    }

    int maxProf = lProf.back();

    for (int i = 1; i < sz - 2; ++i) {
      int comboProf = lProf[i] + rProf[i + 1];
      if (comboProf > maxProf) maxProf = comboProf;
    }

    return maxProf;
  }
};

void test(std::vector<int> vec, int expected) {
  Solution sol;
  int res = sol.maxProfit(vec);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({3, 3, 5, 0, 0, 3, 1, 4}, 6);
  test({7, 6, 4, 3, 1}, 0);
  test({1, 2, 3, 4, 5}, 4);
  test({1}, 0);
  test({1, 2}, 1);
}
