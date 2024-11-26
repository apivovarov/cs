#include <ostream>
#include <array>
#include <functional>
#include <forward_list>

namespace x4444 {
namespace ds {

template <typename T, size_t _Size>
class HashSet {
 protected:
  std::array<std::forward_list<T>, _Size> arr;
  std::hash<T> hh;

 public:
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

  void dump(std::ostream& os) {
    for (auto&& li : arr) {
      for (auto&& el : li) {
        os << el << ",";
      }
    }
    os << std::endl;
  }
};

}  // namespace ds
}  // namespace x4444
