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
  {
    x4444::ds::BST<float> t;
    for (float i : {11., 1.1, 7., 9.1, 19., 4., 5., 23., 2., 9.1, 10., 3.1, 14.,
                    21., 17., 16., 2., 18.}) {
      t.insert(i);
    }

    auto it = t.begin();

    for (int i = 0; i < 3; ++i) {
      std::cerr << "begin-to-end " << i << std::endl;
      while (it != t.end()) {
        std::cerr << *it++ << ",";
      }
      std::cerr << std::endl;
      std::cerr << "back end-to-begin " << i << std::endl;
      do {
        std::cerr << *(--it) << ",";
      } while (it != t.begin());
      std::cerr << std::endl;
    }

    std::cerr << "for loop" << std::endl;
    for (const auto& v : t) {
      std::cerr << v << ", ";
    }
    std::cerr << std::endl;
  }
  {
    x4444::ds::BST<float> t;
    for (float i : {11., 1.1, 7., 9.1, 19., 4., 5., 23., 2., 9.1, 10., 3.1, 14.,
                    21., 17., 16., 2., 18.}) {
      t.insert(i);
    }

    auto ite = t.end();
    for (int i = 0; i < 3; ++i) {
      std::cerr << "end-to-begin " << i << std::endl;
      do {
        std::cerr << *(--ite) << ",";
      } while (ite != t.begin());
      std::cerr << std::endl;
      std::cerr << "back begin-to-end " << i << std::endl;
      while (ite != t.end()) {
        std::cerr << *ite << ",";
        ++ite;
      }
      std::cerr << std::endl;
    }
  }
  std::cerr << "done" << std::endl;
}
