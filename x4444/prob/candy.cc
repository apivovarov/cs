#include <iostream>
#include <vector>

// One way
class Solution {
 public:
  inline void addDownSlopToSum(int& downSlope, int& peak, int& sum) {
    if (peak == -1) {
      sum += (downSlope * downSlope + downSlope) / 2;
    } else {
      if (downSlope < peak) {
        --downSlope;
        sum += (downSlope * downSlope + downSlope) / 2;
      } else {
        sum = sum - peak + 1;
        sum += (downSlope * downSlope + downSlope) / 2;
      }
      peak = -1;
    }
    downSlope = 0;
  }

  int candy(const std::vector<int>& ratings) {
    if (ratings.size() == 1) return 1;
    if (ratings.size() == 2) return ratings[0] != ratings[1] ? 3 : 2;
    int prevV = 1;
    int sum = 1;
    int downSlope = 0;
    bool prevUp = false;
    int peak = -1;
    for (int i = 1; i < ratings.size(); ++i) {
      if (prevUp) {
        if (ratings[i] < ratings[i - 1]) {
          peak = prevV;
        } else if (ratings[i] == ratings[i - 1]) {
          peak = -1;
        }
      }

      int curV = 1;
      if (ratings[i] > ratings[i - 1]) {
        curV = prevV + 1;
      }
      sum += curV;

      if (ratings[i] < ratings[i - 1]) {
        ++downSlope;
      } else if (downSlope > 0) {
        addDownSlopToSum(downSlope, peak, sum);
      }
      prevV = curV;
      prevUp = ratings[i] > ratings[i - 1];
    }
    if (downSlope > 0) {
      addDownSlopToSum(downSlope, peak, sum);
    }
    return sum;
  }
};

// forward abd back
class Solution2 {
 public:
  int candy(const std::vector<int>& ratings) {
    if (ratings.size() == 1) return 1;
    if (ratings.size() == 2) return ratings[0] != ratings[1] ? 3 : 2;
    std::vector<int> res(ratings.size());
    res[0] = 1;
    int backId = -1;
    int sum = 1;
    for (int i = 1; i < ratings.size(); ++i) {
      res[i] = 1;
      if (ratings[i] > ratings[i - 1]) {
        res[i] = res[i - 1] + 1;
      }
      sum += res[i];
      if (ratings[i] < ratings[i - 1]) {
        backId = i + 1;
        sum = res[i];
      }
    }
    if (backId == -1) return sum;
    int prev = res[backId - 1];
    for (int i = backId; i > 1; --i) {
      int cur = res[i - 2];
      if (ratings[i - 2] > ratings[i - 1] && res[i - 2] <= prev) {
        cur = prev + 1;
      }
      sum += cur;
      prev = cur;
    }
    return sum;
  }
};

void test(const std::vector<int>& ratings, int expected) {
  Solution sol;
  int res = sol.candy(ratings);
  if (res != expected) {
    std::cerr << "Error: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({0}, 1);
  test({0, 0}, 2);
  test({0, 1}, 3);
  test({1, 0}, 3);
  test({1, 2, 3}, 6);
  test({3, 2, 1}, 6);
  test({1, 2, 3, 3}, 7);
  test({3, 2, 1, 1}, 7);
  test({3, 2, 1, 2}, 8);
  test({13, 12, 11, 12, 13}, 11);
  // L = R (peak)
  test({11, 11, 12, 13, 12, 11, 11}, 11);
  // L = R (mesa)
  test({11, 11, 12, 13, 13, 12, 11, 11}, 14);

  // L > R (peak)
  test({11, 11, 12, 13, 12, 12}, 9);
  // L > R (mesa)
  test({11, 11, 12, 13, 13, 12, 12}, 11);

  // L < R (peak)
  test({11, 11, 12, 11, 10, 10}, 9);
  // L < R (mesa)
  test({11, 11, 12, 12, 11, 10, 10}, 11);

  test({13, 12, 11, 12, 13, 12, 11}, 14);
  test({1, 0, 2}, 5);
  test({2, 1, 0}, 6);
  test({1, 2, 2}, 4);
  test({60, 80, 100, 100, 100, 100, 100}, 10);
  test({1, 2, 87, 87, 87, 2, 1}, 13);
  test({1, 2, 3, 5, 4, 3, 2, 1}, 21);
  test({1, 2, 3, 5, 4, 3, 2, 1, 4, 3, 2, 1, 3, 2, 1, 1, 2, 3, 4}, 47);
  std::vector<int> a(20000);
  test(a, 20000);
  std::vector<int> b(20000);
  b[19998] = 1;
  test(b, 20001);
}
