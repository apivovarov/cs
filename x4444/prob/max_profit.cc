#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    int max_profit = 0;
    int buy_price = prices[0];

    for (int v : prices) {
      if (v < buy_price) {
        buy_price = v;
        continue;
      }
      int profit = v - buy_price;
      if (profit > max_profit) {
        max_profit = profit;
      }
    }
    return max_profit;
  }
};

void test(std::vector<int> vec, int expected) {
  Solution sol;
  if (sol.maxProfit(vec) != expected) throw std::runtime_error("Bad res");
}

int main() {
  test({30, 29, 28}, 0);
  test({28, 29, 30}, 2);
  test({30, 29, 28, 28, 29, 32, 35, 36}, 8);
  test({30, 29, 28, 28, 29, 32, 35, 36, 35, 34, 33, 33, 34, 43, 50, 47, 35},
       22);
}