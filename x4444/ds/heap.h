#include <iostream>
#include <vector>
#include <stdexcept>

namespace x4444 {
namespace ds {

template <typename T>
class MinHeap {
 protected:
  std::vector<T> vec;

  size_t parent_id(size_t id) {
    if (id == 0) return -1;
    return (id - 1) / 2;
  }

  void heapify(size_t id) {
    for (;;) {
      size_t l_id = id * 2 + 1;
      size_t r_id = l_id + 1;
      size_t min_id = id;
      if (l_id < vec.size() && vec[l_id] < vec[min_id]) min_id = l_id;
      if (r_id < vec.size() && vec[r_id] < vec[min_id]) min_id = r_id;
      if (min_id != id) {
        std::swap(vec[min_id], vec[id]);
        id = min_id;
      } else {
        break;
      }
    }
  }

 public:
  bool empty() {
    return vec.empty();
  }

  size_t size() {
    return vec.size();
  }

  T top() {
    if (vec.empty()) {
      throw std::out_of_range("ERROR: heap is empty");
    }
    return vec[0];
  }

  void push(T v) {
    vec.push_back(v);
    size_t id = vec.size() - 1;
    // compare with parent and swap is needed
    if (id == 0) return;
    size_t pid = parent_id(id);
    while (id > 0 && vec[pid] > vec[id]) {
      std::swap(vec[pid], vec[id]);
      id = pid;
      pid = parent_id(pid);
    }
  }

  void pop() {
    if (vec.empty()) {
      throw std::out_of_range("ERROR: heap is empty");
    }
    if (vec.size() == 1) {
      vec.resize(0);
      return;
    }
    if (vec.size() == 2) {
      vec[0] = vec[1];
      vec.resize(1);
      return;
    }
    size_t last_id = vec.size() - 1;
    vec[0] = vec[last_id];
    vec.resize(last_id);

    heapify(0);
  }

  void dump(std::ostream& os) {
    size_t sz = vec.size();
    size_t a = 0;
    size_t b = 1;
    size_t win_sz = 1;
    size_t i = 0;

    while (i < sz) {
      for (i = a; i < b; ++i) {
        os << vec[i] << " ";
      }
      os << std::endl;
      a = b;
      win_sz *= 2;
      b = std::min(a + win_sz, sz);
    }
  }
};

}  // namespace ds
}  // namespace x4444
