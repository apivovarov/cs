#include <ostream>
#include <array>
#include <functional>
#include "x4444/ds/forward_list.h"

namespace x4444 {
namespace ds {

template <typename T, size_t _Size>
class HashSet {
 protected:
  std::array<ForwardList<T>, _Size> arr;
  std::hash<T> hh;

 public:
  class Iterator {
   protected:
    std::array<ForwardList<T>, _Size>::iterator it0;
    const std::array<ForwardList<T>, _Size>::iterator ite0;
    ForwardList<T>::Iterator it1;
    ForwardList<T>::Iterator ite1;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    Iterator(std::array<ForwardList<T>, _Size>::iterator _it0,
             std::array<ForwardList<T>, _Size>::iterator _ite0,
             ForwardList<T>::Iterator _it1, ForwardList<T>::Iterator _ite1)
        : it0(_it0), ite0(_ite0), it1(_it1), ite1(_ite1) {
      if (it0 != ite0 && it1 == ite1) {
        ++(*this);
      }
    }

    reference operator*() const { return *it1; }

    pointer operator->() const { return (*it1).operator->(); }

    Iterator& operator++() {
      if (it1 != ite1) {
        ++it1;
      }
      while (it1 == ite1) {
        ++it0;
        if (it0 == ite0) {
          return *this;
        }
        it1 = (*it0).begin();
        ite1 = (*it0).end();
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const Iterator& other) const {
      return it0 == other.it0 && it1 == other.it1;
    }

    bool operator!=(const Iterator& other) const { return !(*this == other); }
  };

  Iterator begin() {
    auto _it0 = arr.begin();
    auto _ite0 = arr.end();
    if (_it0 == _ite0) {
      ForwardList<T> tmp;
      auto _ite1 = tmp.end();
      return Iterator(_it0, _ite0, _ite1, _ite1);
    } else {
      auto _it1 = (*_it0).begin();
      auto _ite1 = (*_it0).end();
      return Iterator(_it0, _ite0, _it1, _ite1);
    }
  }

  Iterator end() {
    auto _ite0 = arr.end();
    ForwardList<T> tmp;
    auto _ite1 = tmp.end();
    return Iterator(_ite0, _ite0, _ite1, _ite1);
  }

  void insert(T v) {
    auto&& li = arr[hh(v) % arr.size()];
    li.remove(v);
    li.push_front(v);
  }

  bool contains(T v) {
    auto&& li = arr[hh(v) % arr.size()];
    for (auto&& el : li) {
      if (el == v) {
        return true;
      }
    }
    return false;
  }

  void remove(T v) {
    auto&& li = arr[hh(v) % arr.size()];
    li.remove(v);
  }
};

}  // namespace ds
}  // namespace x4444
