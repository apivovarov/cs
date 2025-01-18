#include <iostream>
#include <vector>
#include <string>

// 97. Interleaving String
class Solution {
 public:
  bool isInterleave(const std::string& s1, const std::string& s2,
                    const std::string& s3) {
    int sz1 = s1.size();
    int sz2 = s2.size();
    int sz3 = s3.size();
    if (sz1 == 0 && sz2 == 0) return sz3 == 0;
    if (sz1 == 0) return s2 == s3;
    if (sz2 == 0) return s1 == s3;
    if (sz1 + sz2 != sz3) return false;

    std::vector<std::vector<int>> dp(sz1 + 1, std::vector<int>(sz2 + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i <= sz1; ++i) {
      for (int j = 0; j <= sz2; ++j) {
        int id = dp[i][j];
        if (id == -1) continue;
        char c3 = s3[id];
        // down
        // int id1 = i;
        if (i < sz1 && s1[i] == c3) {
          dp[i + 1][j] = id + 1;
        }
        // right
        // int id2 = j;
        if (j < sz2 && s2[j] == c3) {
          dp[i][j + 1] = id + 1;
        }
      }
    }
    return dp[sz1][sz2] == sz3;
  }
};

void test(const std::string& s1, const std::string& s2, const std::string& s3,
          bool expected) {
  Solution sol;
  bool res = sol.isInterleave(s1, s2, s3);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test("aabcc", "dbbca", "aadbbcbcac", true);
  test("aabcc", "dbbca", "aadbbbaccc", false);
  test("", "", "", true);
}
