#include "x4444/ds/hashset.h"
#include <iostream>

int main() {
  x4444::ds::HashSet<int, 1024> hs;
  hs.insert(492049093);
  hs.insert(15);
  hs.insert(15);
  hs.insert(1039);
  hs.insert(492049093);

  std::cerr << "size: " << hs.size() << std::endl;
  std::cerr << "iter loop" << std::endl;
  for (auto it = hs.begin(); it != hs.end(); ++it) {
    std::cerr << *it << ", ";
  }
  std::cerr <<  std::endl;
  std::cerr << "iter loop done" << std::endl;
  std::cerr << "for loop" << std::endl;
  for(auto&& v : hs) {
    std::cerr << v << ", ";
  }
  std::cerr <<  std::endl;
  std::cerr << "for loop done" << std::endl;

  std::cerr << "contains(44): " << std::boolalpha << hs.contains(44)
            << std::endl;
  std::cerr << "contains(15): " << std::boolalpha << hs.contains(15)
            << std::endl;
  std::cerr << "contains(1039): " << std::boolalpha << hs.contains(1039)
            << std::endl;
  std::cerr << "contains(492049093): " << std::boolalpha
            << hs.contains(492049093) << std::endl;

  std::cerr << "erase(15): " << std::endl;
  hs.erase(15);
  std::cerr << "contains(15): " << std::boolalpha << hs.contains(15)
            << std::endl;

  std::cerr << "size: " << hs.size() << std::endl;
}
