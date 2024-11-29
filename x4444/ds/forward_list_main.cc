#include "x4444/ds/forward_list.h"
#include <iostream>

struct Foo {
  int a;
  int b;
  void print() { std::cerr << a << " " << b << std::endl; }
};

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

  for (auto it = li.begin(); it != li.end(); ++it) {
    std::cerr << *it << ",";
  }
  std::cerr << std::endl;

  for (auto it = li.cbegin(); it != li.cend(); ++it) {
    std::cerr << *it << ",";
  }
  std::cerr << std::endl;

  for (const int& v : li) {
    std::cerr << v << ",";
  }
  std::cerr << std::endl;

  auto it1 = li.begin();
  auto it2 = li.begin();
  ++it2;
  ++it2;

  // Calculate distance between iterators
  auto dist = std::distance(it1, it2);
  std::cerr << "Distance between iterators: " << dist << std::endl;

  x4444::ds::ForwardList<Foo> foo_li;
  foo_li.push_front({1, 2});
  foo_li.push_front({3, 4});

  for (auto foo_it = foo_li.begin(); foo_it != foo_li.end(); ++foo_it) {
    foo_it->print();
  }
}
