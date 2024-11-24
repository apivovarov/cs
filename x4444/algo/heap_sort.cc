#include "x4444/ds/heap.h"
#include <iostream>

void heap_sort(float * a, int sz) {
    x4444::ds::MinHeap<float> h;
    for (int i = 0; i < sz; ++i) {
        h.push(a[i]);
    }
    for (int i = 0; i < sz; ++i) {
      a[i] = h.top();
      h.pop();
    }
}

int main() {
  std::array<float, 17> a = {5.,  1., 8., 33.3, 3., 9.1, 4.,   1.,  -4.2,
                             -7., 7., 8., 5.5,  2., 6.,  18.3, 4.44};
  heap_sort(a.data(), a.size());

  for (auto&& v : a) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
