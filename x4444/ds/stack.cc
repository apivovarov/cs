#include "x4444/ds/stack.h"
#include <iostream>

int main() {
  x4444::ds::Stack<float> s;
  float a = 3.5;
  s.push(a);
  s.push(4.8);
  s.push(9.3);
  s.push(5.1);
  std::cerr << s.size() << std::endl;
  while (!s.empty()) {
    std::cerr << "head: " << s.head() << std::endl;
    s.pop();
  }
}
