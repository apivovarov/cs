#include <iostream>
#include <vector>

struct Node {
  float profit;
  float weight;
};

int main() {
  std::vector<Node> input = {{100, 20}, {60, 10}, {120, 30}};
  float W = 10.;
  std::vector<float> res(input.size(), 0.0);
  float totalProfit = 0.;

  std::sort(input.begin(), input.end(), [](const Node& a, const Node& b) {
    return a.profit / a.weight > b.profit / b.weight;
  });

  for (int i = 0; i < input.size(); ++i) {
    const Node& n = input[i];
    if (W < n.weight) {
      // take fraction
      float fr = W / n.weight;
      res[i] = fr;
      W = 0;
      totalProfit += n.profit * fr;
      break;
    }
    // take whole;
    res[i] = 1.0;
    W -= n.weight;
    totalProfit += n.profit;
  }

  for (int i = 0; i < input.size(); ++i) {
    const Node& n = input[i];
    std::cout << i << ": " << n.profit << "," << n.weight << " take: " << res[i]
              << std::endl;
  }
  std::cout << "Total Profit: " << totalProfit << std::endl;
}
