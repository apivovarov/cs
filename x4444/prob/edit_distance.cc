#include <iostream>
#include <vector>
#include <string>

// 72. Edit Distance
class Solution {
 public:
  int minDistance(const std::string& word1, const std::string& word2) {
    int sz1 = word1.size();
    int sz2 = word2.size();
    if (sz1 == 0) return sz2;
    if (sz2 == 0) return sz1;

    std::vector<std::vector<int>> dp(sz1 + 1, std::vector<int>(sz2 + 1));

    for (int j = 1; j <= sz2; ++j) dp[0][j] = j;
    for (int i = 1; i <= sz1; ++i) dp[i][0] = i;

    for (int i = 1; i <= sz1; ++i) {
      for (int j = 1; j <= sz2; ++j) {
        // same char
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          int v =
              dp[i - 1][j - 1] < dp[i - 1][j] ? dp[i - 1][j - 1] : dp[i - 1][j];
          v = v < dp[i][j - 1] ? v : dp[i][j - 1];
          dp[i][j] = v + 1;
        }

      }
    }
    return dp[sz1][sz2];
  }
};

void test(const std::string& word1, const std::string& word2, int expected) {
  Solution sol;
  int res = sol.minDistance(word1, word2);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test("horse", "ros", 3);
  test("intention", "execution", 5);
  test("a", "a", 0);
}
