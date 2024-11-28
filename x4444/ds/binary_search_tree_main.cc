#include "x4444/ds/binary_search_tree.h"
#include <iostream>

int main() {
  x4444::ds::BST<float> t;
  for (float i : {11., 1.1, 7., 9.1, 19., 4., 5., 23., 2., 9.1, 10., 3.1, 14.,
                  21., 17., 16., 2., 18.}) {
    t.insert(i);
  }

  t.dump(std::cerr);

  std::cout << "contains 55: " << std::boolalpha << t.contains(55.)
            << std::endl;
  std::cout << "contains -55: " << std::boolalpha << t.contains(-55.)
            << std::endl;
  std::cout << "contains 6: " << std::boolalpha << t.contains(6.) << std::endl;
  std::cout << "contains 16: " << std::boolalpha << t.contains(16.)
            << std::endl;
  std::cout << "contains 7: " << std::boolalpha << t.contains(7.) << std::endl;

  std::cout << "max: " << t.max() << std::endl;
  std::cout << "min: " << t.min() << std::endl;

  std::cout << "size: " << t.size() << std::endl;

  for (float i : {66., 21., 11., 19., 3.1, 14., 17., 1.1, 23., 10., 5., 16.,
                  16., 7., 9.1, 18., 4., 2.}) {
    std::cerr << "==============================" << std::endl;
    t.dump(std::cerr);
    std::cerr << "erasing: " << i << ", res: " << t.erase(i) << std::endl;
    t.dump(std::cerr);
  }

  {
    x4444::ds::BST<float> t2;
    t2.insert(4.55);
    t2.insert(5.55);
    t2.insert(1.55);
    t2.insert(6.55);
    t2.insert(2.55);
    t2.insert(9.55);
    t2.insert(4.55);
    t2.insert(6.55);
    t2.insert(1.45);
  }
  std::cerr << "done" << std::endl;
}
