#include <iostream>
#include <queue>
#include <vector>

struct CapProf {
  int cap;
  int prof;
};

struct GreaterCap {
  bool operator()(const CapProf& a, const CapProf& b) const {
    return a.cap > b.cap;
  }
};

// 502. IPO
class Solution {
 public:
  int findMaximizedCapital(int k, int w, const std::vector<int>& profits,
                           const std::vector<int>& capital) {
    // Greater comparison gives smallest cap on top
    std::priority_queue<CapProf, std::vector<CapProf>, GreaterCap> cap_pq;
    for (int i = 0; i < profits.size(); ++i) {
      cap_pq.emplace(CapProf{capital[i], profits[i]});
    }
    // default less comparison gives largest on top.
    std::priority_queue<int> profit_pq;

    while (k > 0) {
      // not enough capital. stop.
      while (!cap_pq.empty() && cap_pq.top().cap <= w) {
        profit_pq.push(cap_pq.top().prof);
        cap_pq.pop();
      }

      // no projects to pick
      if (profit_pq.empty()) break;
      // take largest profit for 1 k
      w += profit_pq.top();
      profit_pq.pop();
      --k;
    }
    return w;
  }
};

void test(int k, int w, const std::vector<int>& profits,
          const std::vector<int>& capital, int expected) {
  Solution sol;
  int res = sol.findMaximizedCapital(k, w, profits, capital);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test(2, 0, {1, 2, 3}, {0, 1, 1}, 4);
  test(3, 0, {1, 2, 3}, {0, 1, 2}, 6);
}
