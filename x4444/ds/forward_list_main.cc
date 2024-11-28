#include "x4444/ds/forward_list.h"
#include <iostream>

int main() {
  x4444::ds::ForwardList<int> li;
  li.push_front(4);
  li.push_front(4);
  li.push_front(5);
  li.push_front(2);
  li.push_front(4);
  li.push_front(8);
  li.push_front(1);
  li.push_front(4);
  li.dump(std::cerr);
  std::cerr << "Front: " << li.front() << std::endl;
  std::cerr << "remove(4)" << std::endl;
  li.remove(4);
  li.dump(std::cerr);
  std::cerr << "Front: " << li.front() << std::endl;
  std::cerr << "pop_front()" << std::endl;
  li.pop_front();
  li.dump(std::cerr);
  std::cerr << "Front: " << li.front() << std::endl;
}
