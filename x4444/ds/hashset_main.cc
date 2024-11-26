#include "x4444/ds/hashset.h"
#include <iostream>

int main() {
  x4444::ds::HashSet<int, 1024> hs;
  hs.insert(492049093);
  hs.insert(15);
  hs.insert(15);
  hs.insert(1039);
  hs.insert(492049093);
  hs.dump(std::cerr);

  std::cerr << "contains(44): " << std::boolalpha << hs.contains(44)
            << std::endl;
  std::cerr << "contains(15): " << std::boolalpha << hs.contains(15)
            << std::endl;
  std::cerr << "contains(1039): " << std::boolalpha << hs.contains(1039)
            << std::endl;
  std::cerr << "contains(492049093): " << std::boolalpha
            << hs.contains(492049093) << std::endl;

  std::cerr << "remove(15): " << std::endl;
  hs.remove(15);
  std::cerr << "contains(15): " << std::boolalpha << hs.contains(15)
            << std::endl;
}
