#include <iostream>
#include <vector>

// 130. Surrounded Regions
class Solution {
 public:
  void visit(int i, int j, std::vector<std::vector<char>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    if (i < 0 || j < 0 || i >= rows || j >= cols) return;
    if (board[i][j] != 'O') return;
    board[i][j] = 'R';
    visit(i - 1, j, board);
    visit(i, j - 1, board);
    visit(i + 1, j, board);
    visit(i, j + 1, board);
  }

  void solve(std::vector<std::vector<char>>& board) {
    if (board.empty() || board[0].empty()) return;
    int rows = board.size();
    int cols = board[0].size();
    if (rows <= 2 || cols <= 2) return;

    for (int j = 0; j < cols; ++j) {
      if (board[0][j] == 'O') visit(0, j, board);
      if (board[rows - 1][j] == 'O') visit(rows - 1, j, board);
    }
    for (int i = 1; i < rows - 1; ++i) {
      if (board[i][0] == 'O') visit(i, 0, board);
      if (board[i][cols - 1] == 'O') visit(i, cols - 1, board);
    }
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (board[i][j] == 'R') {
          board[i][j] = 'O';
        } else if (board[i][j] == 'O') {
          board[i][j] = 'X';
        }
      }
    }
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

int main() {
  {
    std::vector<std::vector<char>> board = {{'X', 'X', 'X', 'X'},
                                            {'X', 'O', 'O', 'X'},
                                            {'X', 'X', 'O', 'X'},
                                            {'X', 'O', 'X', 'X'}};
    Solution sol;
    sol.solve(board);
    std::cerr << "----------------------------------" << std::endl;
    for (auto& vv : board) {
      std::cerr << vv << std::endl;
    }
  }
  {
    std::vector<std::vector<char>> board = {{'X'}};
    Solution sol;
    sol.solve(board);
    std::cerr << "----------------------------------" << std::endl;
    for (auto& vv : board) {
      std::cerr << vv << std::endl;
    }
  }
  {
    std::vector<std::vector<char>> board = {{'X', 'X', 'X', 'X'},
                                            {'X', 'O', 'O', 'X'},
                                            {'X', 'X', 'O', 'X'},
                                            {'X', 'O', 'X', 'X'},
                                            {'X', 'O', 'X', 'X'}};
    Solution sol;
    sol.solve(board);
    std::cerr << "----------------------------------" << std::endl;
    for (auto& vv : board) {
      std::cerr << vv << std::endl;
    }
  }
  {
    std::vector<std::vector<char>> board = {{'X', 'X', 'X', 'X'},
                                            {'O', 'O', 'O', 'X'},
                                            {'X', 'X', 'O', 'X'},
                                            {'X', 'O', 'X', 'X'},
                                            {'X', 'O', 'X', 'X'}};
    Solution sol;
    sol.solve(board);
    std::cerr << "----------------------------------" << std::endl;
    for (auto& vv : board) {
      std::cerr << vv << std::endl;
    }
  }
}
