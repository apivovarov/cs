#include <iostream>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    if (i > 0 && i % 6 == 0) os << "  ";
    os << arr[i];
  }
  os << "]";
  return os;
}

#include <vector>
#include <queue>

// 909. Snakes and Ladders - BFS approach - fastest
class Solution {
  inline int getV(const std::vector<std::vector<int>>& board, int n) {
    int N = board.size();
    int R0 = n / N;
    int R = N - R0 - 1;  // reverse rowId (0-based)
    int C = n % N;
    if (R0 % 2 == 1) C = N - C - 1;  // reverse colId for odd rows (0-based)
    // std::cerr << "n: " << n << ", R: " << R << ", C: " << C << std::endl;
    int v = board[R][C];         // get value
    return v == -1 ? n : v - 1;  // returt original index or value (0-based)
  }

 public:
  int snakesAndLadders(const std::vector<std::vector<int>>& board) {
    int N = board.size();
    std::queue<int> qu;
    qu.push(0);
    std::vector<bool> visited(N * N);
    int cnt = 1;
    // BFS
    while (!qu.empty()) {
      // std::cerr << "dice: " << cnt << std::endl;
      int qsz = qu.size();
      for (int i = 0; i < qsz; ++i) {
        int cid = qu.front();
        qu.pop();
        // std::cerr << "  cid: " << cid << std::endl;
        // get neib
        for (int k = 1; k <= 6; ++k) {
          int neibId = cid + k;
          if (neibId >= N * N) break;
          neibId = getV(board, neibId);
          // std::cerr << "    neibId: " << neibId << std::endl;
          if (visited[neibId]) continue;
          visited[neibId] = true;
          if (neibId == N * N - 1) return cnt;
          qu.push(neibId);
        }
      }
      ++cnt;
    }
    return -1;
  }
};

// 909. Snakes and Ladders - DP approach - not very fast
class SolutionDP {
  std::vector<std::vector<int>> _board;
  int N;

  int getV(int n) {
    int R0 = n / N;
    int R = N - R0 - 1;  // reverse rowId (0-based)
    int C = n % N;
    if (R0 % 2 == 1) C = N - C - 1;  // reverse colId for odd rows (0-based)
    // std::cerr << "n: " << n << ", R: " << R << ", C: " << C << std::endl;
    return _board[R][C] - 1;  // convert value to 0-based
  }

 public:
  int snakesAndLadders(const std::vector<std::vector<int>>& board) {
    _board = board;
    N = board.size();
    std::vector<int> res(N * N, -1);
    res[0] = 0;

    for (int i = 0; i < N * N; ++i) {
      //      int destId = getV(i);
      // std::cerr << "i:" << i << ", dstId: " << destId << std::endl;
      int currV = res[i];
      if (currV < 0) continue;
      int minJumpId = i;
      for (int k = 1; k <= 6; ++k) {
        int j = i + k;
        if (j >= N * N) break;

        //        jump[j] = false;
        int jumpId = getV(j);
        if (jumpId >= 0) {
          j = jumpId;
        }
        if (res[j] < 0 || currV + 1 < res[j]) {
          res[j] = currV + 1;
          if (j < minJumpId) minJumpId = jumpId;
        }
      }
      if (minJumpId < i) {
        // std::cerr << "minJumpId: " << minJumpId << ", i: " << i <<std::endl;
        // std::cerr << res << std::endl;
        i = minJumpId - 1;
      }
    }
    std::cerr << res << std::endl;
    return res[N * N - 1];
  }
};

void test(const std::vector<std::vector<int>>& board, int expected) {
  Solution sol;
  int res = sol.snakesAndLadders(board);
  if (res != expected) {
    std::cerr << "ERROR: res: " << res << std::endl;
  }
}

int main() {
  test({{-1, 35, 34, 33, 32, 31},
        {25, 26, 27, 28, 29, 30},
        {24, 23, 22, 21, 20, 19},
        {13, 14, 15, 16, 17, 18},
        {12, 11, 10, 9, 8, 7},
        {-1, 2, 3, 4, 5, 6}},
       6);

  test({{-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 35, -1, -1, 13, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 15, -1, -1, -1, -1}},
       4);

  // case wiht two laddeds connected together
  test({{-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 35, -1, -1, 13, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 14, -1, -1, -1, -1}},
       4);

  test({{-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {18, 17, 16, 15, 14, 13},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1}},
       -1);

  test({{-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 17, 16, 15, 14, 13},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1}},
       6);

  test({{-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1},
        {-1, 24, -1, -1, 13},
        {-1, -1, -1, -1, -1},
        {-1, 15, -1, -1, -1}},
       3);

  test({{-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, 2},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1}},
       6);

  test({{-1, -1, -1}, {-1, 9, 8}, {-1, 8, 9}}, 1);
  test({{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}, 2);
  test({{-1, -1, -1}, {-1, -1, -1}, {-1, -1, 8}}, 2);
  test({{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, 8}},
       3);
  test({{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, 10}},
       2);

  test({{-1, 1, 2, -1}, {2, 13, 15, -1}, {-1, 10, -1, -1}, {-1, 6, 2, 8}}, 2);
  test({{-1, -1}, {-1, 3}}, 1);
  test({{-1, -1, -1}, {2, -1, -1}, {-1, -1, -1}}, 2);
}
