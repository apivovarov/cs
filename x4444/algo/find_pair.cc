#include <iostream>

int arr[] = {1, 2, 3, 4, 4, 6, 7, 9, 15};
int sz = 9;
int target = 8;

int main() {
  int a = 0;
  int b = sz - 1;

  while (a < b) {
    int s = arr[a] + arr[b];
    if (s > target) {
      // move b left
      --b;
    } else if (s < target) {
      // move a right
      ++a;
    } else {
      std::cout << "[" << a << "]:" << arr[a] << ", [" << b << "]:" << arr[b]
                << std::endl;
      --b;
      ++a;
    }
  }
}
