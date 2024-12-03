#include <iostream>
#include <vector>
#include <array>
#include <limits>

int main() {
  const std::vector<int> avail_coins = {1, 2, 5, 10, 25};
  std::array<int, 101> cnt = {};
  cnt[0] = 0;

  for (int i = 1; i < cnt.size(); ++i) {
    for (int coin : avail_coins) {
      if (i < coin) break;
      int prev_id = i - coin;
      int new_cnt = cnt[prev_id] + 1;
      if (cnt[i] == 0 || new_cnt < cnt[i]) cnt[i] = new_cnt;
    }
  }

  for (int i = 0; i < cnt.size(); ++i) {
    std::cout << i << ": " << cnt[i] << std::endl;
  }
}
