#include <vector>
#include <functional>
#include <iostream>
#include <utility>

namespace x4444::algo {

template <typename T, class Compare>
void __heapify_up(T* arr, size_t sz, Compare&& cmp) {
  size_t id = sz - 1;
  while (id > 0) {
    size_t parent = (id - 1) / 2;
    if (!cmp(arr[parent], arr[id])) break;
    std::swap(arr[id], arr[parent]);
    id = parent;
  }
}

template <typename T, class Compare>
void __heapify_down(T* arr, size_t sz, size_t parent, Compare&& cmp) {
  while (true) {
    size_t largest = parent;
    size_t ch0 = 2 * parent + 1;
    size_t ch1 = ch0 + 1;

    if (ch0 < sz && cmp(arr[largest], arr[ch0])) largest = ch0;
    if (ch1 < sz && cmp(arr[largest], arr[ch1])) largest = ch1;

    if (largest != parent) {
      std::swap(arr[largest], arr[parent]);
      parent = largest;
    } else {
      break;
    }
  }
}

template <typename T, class Compare>
void make_heap(T* arr, size_t sz, Compare&& cmp) {
  if (sz < 2) return;
  size_t parent = sz / 2 - 1;  // parent of the last node;
  while (true) {
    __heapify_down(arr, sz, parent, std::forward<Compare>(cmp));
    if (parent == 0) break;  // parent is unsigned
    --parent;
  }
}

template <typename T>
void make_heap(T* arr, size_t sz) {
  return make_heap(arr, sz, std::less<T>());
}

template <typename T, class Compare>
void pop_heap(T* arr, size_t sz, Compare&& cmp) {
  if (sz < 2) return;
  std::swap(arr[0], arr[sz - 1]);
  __heapify_down(arr, sz - 1, 0, std::forward<Compare>(cmp));
}

template <typename T>
void pop_heap(T* arr, size_t sz) {
  pop_heap(arr, sz, std::less<T>());
}

template <typename T, class Compare>
void push_heap(T* arr, size_t sz, Compare&& cmp) {
  if (sz < 2) return;
  __heapify_up(arr, sz, std::forward<Compare>(cmp));
}

template <typename T>
void push_heap(T* arr, size_t sz) {
  push_heap(arr, sz, std::less<T>());
}

template <typename T, class Compare>
bool is_heap(T* arr, size_t sz, Compare&& cmp) {
  if (sz < 2) return true;
  size_t last_parent = sz / 2 - 1;
  for (size_t id = 0; id <= last_parent; ++id) {
    size_t ch0 = 2 * id + 1;
    size_t ch1 = ch0 + 1;
    if (ch0 < sz && cmp(arr[id], arr[ch0])) return false;
    if (ch1 < sz && cmp(arr[id], arr[ch1])) return false;
  }
  return true;
}

template <typename T>
bool is_heap(T* arr, size_t sz) {
  return is_heap(arr, sz, std::less<T>());
}

}  // namespace x4444::algo

template <typename T>
void dump(T&& it, T&& end) {
  while (it != end) {
    std::cout << *it++ << ",";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<float> a = {5.,  1., 8., 33.3, 3., 9.1, 4., 1.,   -4.2,
                          -7., 7., 8., 5.5,  2., 6.,  7., 18.3, 4.44};

  // std::vector<float>  a = {19, 6,  19, 39, -3, 111, 0,   -1,  19, 2,
  //                            -5, 13, 4,  -5, 19, 6,   111, 111, 111};
  // std::vector<float> a = {1, 0, 1, 0, 1, 0, 1, -2};
  std::cout << "Input:" << std::endl;
  dump(a.cbegin(), a.cend());
  std::cout << "Is heap: " << std::boolalpha
            << x4444::algo::is_heap(a.data(), a.size()) << std::endl;

  std::cout << "Make heap:" << std::endl;
  x4444::algo::make_heap(a.data(), a.size());
  dump(a.cbegin(), a.cend());
  std::cout << "Is heap: " << std::boolalpha
            << x4444::algo::is_heap(a.data(), a.size()) << std::endl;

  std::cout << "Push heap 15.7:" << std::endl;
  a.push_back(15.7);
  x4444::algo::push_heap(a.data(), a.size());
  dump(a.cbegin(), a.cend());
  std::cout << "Is heap: " << std::boolalpha
            << x4444::algo::is_heap(a.data(), a.size()) << std::endl;

  std::cout << "Pop heap loop:" << std::endl;
  for (size_t sz = a.size(); sz > 1; --sz) {
    x4444::algo::pop_heap(a.data(), sz);
    dump(a.cbegin(), a.cend());
  }
  std::cout << "Is heap: " << std::boolalpha
            << x4444::algo::is_heap(a.data(), a.size()) << std::endl;
}
