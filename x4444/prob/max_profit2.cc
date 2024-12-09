#include <vector>

class Solution {
 public:
  int maxProfit2(std::vector<int>& prices) {
    int max_profit = 0;
    int buy_price = prices[0];
    int pos = 0;
    for (int i = 1; i < prices.size(); ++i) {
      if (prices[i - 1] < prices[i]) {
        max_profit += prices[i] - prices[i - 1];
      }
    }

    return max_profit;
  }
};

void test(std::vector<int> vec, int expected) {
  Solution sol;
  if (sol.maxProfit2(vec) != expected) throw std::runtime_error("Bad res");
}

int main() {
  test({30, 29, 28}, 0);
  test({28, 29, 30}, 2);
  test({30, 29, 28, 28, 29, 32, 35, 36}, 8);
  test({30, 29, 28, 28, 29, 32, 35, 36, 35, 34, 33, 33, 34, 43, 50, 47, 35, 37},
       8 + 17 + 2);
}