#include <iostream>
#include <string>
#include <vector>

// 52. N-Queens II
class Solution {
 public:
  void backtrack(int n, int R, std::vector<bool>& cols,
                 std::vector<bool>& udiag, std::vector<bool>& ddiag, int& cnt) {
    if (R == n) {
      ++cnt;
      return;
    }
    for (int C = 0; C < n; ++C) {
      if (cols[C]) continue;
      int u = C + R;
      if (udiag[u]) continue;
      int d = C - R + n - 1;
      if (ddiag[d]) continue;
      cols[C] = true;
      udiag[u] = true;
      ddiag[d] = true;
      backtrack(n, R + 1, cols, udiag, ddiag, cnt);
      ddiag[d] = false;
      udiag[u] = false;
      cols[C] = false;
    }
  }

  int totalNQueens(int n) {
    std::vector<bool> cols(n);
    std::vector<bool> udiag(2 * n - 1);
    std::vector<bool> ddiag(2 * n - 1);
    int cnt = 0;
    backtrack(n, 0, cols, udiag, ddiag, cnt);
    return cnt;
  }
};

void test(int n, int expected) {
  Solution sol;
  int res = sol.totalNQueens(n);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test(1, 1);
  test(2, 0);
  test(3, 0);
  test(4, 2);
  test(5, 10);
  test(6, 4);
  test(7, 40);
  test(8, 92);
  test(9, 352);
}
