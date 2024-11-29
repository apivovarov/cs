#include "x4444/ds/stack.h"
#include <iostream>

int main() {
  x4444::ds::Stack<float> s;
  float a = 3.5;
  s.push(a);
  s.push(4.8);
  s.push(9.3);
  s.push(5.1);
  std::cerr << "size: " << s.size() << std::endl;

  std::cerr << "iter loop" << std::endl;
  for (auto it = s.begin(); it != s.end(); ++it) {
    std::cerr << *it << ", ";
  }
  std::cerr << std::endl;
  std::cerr << "iter loop done" << std::endl;

  std::cerr << "for loop" << std::endl;
  for (auto v : s) {
    std::cerr << v << ", ";
  }
  std::cerr << std::endl;
  std::cerr << "for loop done" << std::endl;

  while (!s.empty()) {
    std::cerr << "head: " << s.head() << std::endl;
    s.pop();
  }
}
