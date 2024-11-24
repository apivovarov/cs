#include <iostream>
#include <array>
#include <unordered_set>

std::array<int, 11> arrs{-5, -1, 1, 2, 3, 4, 4, 6, 7, 9, 15};
std::array<int, 11> arrns{7, 4, 1, 9, 3, 4, -1, 6, -5, 2, 15};
constexpr int sz = arrs.size();
int target = 8;

void find_in_sorted() {
  int a = 0;
  int b = sz - 1;

  while (a < b) {
    int s = arrs[a] + arrs[b];
    if (s > target) {
      // move b left
      --b;
    } else if (s < target) {
      // move a right
      ++a;
    } else {
      std::cout << "[" << a << "]:" << arrs[a] << ", [" << b << "]:" << arrs[b]
                << std::endl;
      --b;
      ++a;
    }
  }
}

void find_in_not_sorted() {
  std::unordered_set<int> ss;
  ss.insert(arrns[0]);
  int i = 1;
  while (i < sz) {
    int key = target - arrns[i];
    if (ss.count(key) == 1) {
      std::cout << key << ", " << arrns[i] << std::endl;
      ss.erase(key);
    } else {
      ss.insert(arrns[i]);
    }
    ++i;
  }
}

int main() {
  std::cout << "== find_in_sorted ==" << std::endl;
  find_in_sorted();
  std::cout << "== find_in_not_sorted ==" << std::endl;
  find_in_not_sorted();
}
