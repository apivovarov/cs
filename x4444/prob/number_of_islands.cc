#include <iostream>
#include <vector>

// 200. Number of Islands
class Solution {
 public:
  void visit(int i, int j, std::vector<std::vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    if (i < 0 || j < 0 || i >= rows || j >= cols) return;
    if (grid[i][j] == '0') return;
    grid[i][j] = '0';
    visit(i - 1, j, grid);
    visit(i, j - 1, grid);
    visit(i + 1, j, grid);
    visit(i, j + 1, grid);
  }

  int numIslands(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int cnt = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] == '1') {
          visit(i, j, grid);
          ++cnt;
        }
      }
    }
    return cnt;
  }
};

void test(const std::vector<std::vector<char>>& _grid, int expected) {
  Solution sol;
  std::vector<std::vector<char>> grid = _grid;
  int res = sol.numIslands(grid);

  if (res != expected) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}},
       1);

  test({{'1', '1', '1', '1', '0', '1', '1', '0', '1', '0'}}, 3);
}
