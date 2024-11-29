#include "x4444/ds/heap.h"
#include <iostream>

int main() {
  x4444::ds::MinHeap<float> h;
  float sample1[] = {148, 151, 12, 5, 8, 150, 14, 6, 7, 20, 30, 160, 152, 4, 132};
  for (float i : sample1) {
    h.push(i);
  }

  std::cerr << "top: " << h.top() << ", size: " << h.size() << std::endl;
  h.dump(std::cerr);
  std::cerr << "iter loop" << std::endl;
  for (auto it = h.begin(); it != h.end(); ++it) {
    std::cerr << *it << ", ";
  }
  std::cerr << std::endl;
  std::cerr << "iter loop done" << std::endl;
  std::cerr << "for loop" << std::endl;
  for (auto&& v : h) {
    std::cerr << v << ", ";
  }
  std::cerr << std::endl;
  std::cerr << "for loop done" << std::endl;

  while (h.size() > 0) {
    std::cerr << "=======================" << std::endl;
    h.pop();
    if (h.empty()) {
      break;
    }
    std::cerr << "top: " << h.top() << ", size: " << h.size()
              << std::endl;
    h.dump(std::cerr);
  }
}
