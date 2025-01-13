#include <iostream>
#include <string>
#include <vector>

// 79. Word Search
class Solution {
 public:
  bool visit(int R, int C, int pos, std::vector<std::vector<char>>& board,
             const std::string& word) {
    if (pos >= word.size()) return true;
    int Rsz = board.size();
    int Csz = board[0].size();
    if (R < 0 || C < 0 || R >= Rsz || C >= Csz) return false;
    char c = board[R][C];
    if (word[pos] != c) return false;
    board[R][C] = '*';
    std::array<int, 5> rot = {0, -1, 0, 1, 0};
    for (int i = 0; i < 4; ++i) {
      if (visit(R + rot[i + 1], C + rot[i], pos + 1, board, word)) return true;
    }
    board[R][C] = c;
    return false;
  }

  bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
    int Rsz = board.size();
    int Csz = board[0].size();
    if (word.size() > Rsz * Csz) return false;

    for (int R = 0; R < Rsz; ++R) {
      for (int C = 0; C < Csz; ++C) {
        if (visit(R, C, 0, board, word)) return true;
      }
    }

    return false;
  }
};

void test(const std::vector<std::vector<char>>& _board, const std::string& word,
          bool expected) {
  Solution sol;
  std::vector<std::vector<char>> board = _board;
  bool res = sol.exist(board, word);
  if (res != expected) {
    std::cerr << "ERROR: res: " << std::boolalpha << res << std::endl;
  }
}

int main() {
  test({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
       "ABCCED", true);

  test({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
       "ABCFC", false);
}
