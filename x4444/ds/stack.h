#include <vector>
#include <stdexcept>

namespace x4444 {
namespace ds {

template <typename T>
class Stack {
 protected:
  std::vector<T> vec;

 public:
  using iterator = typename std::vector<T>::reverse_iterator;

  iterator begin() { return vec.rbegin(); }

  iterator end() { return vec.rend(); }

  void push(const T& i) { vec.push_back(i); }
  void push(T&& i) { vec.push_back(std::move(i)); }
  void pop() {
    if (vec.empty()) throw std::out_of_range("Stack is empty");
    vec.pop_back();
  }
  T head() {
    if (vec.empty()) throw std::out_of_range("Stack is empty");
    return vec[vec.size() - 1];
  }
  size_t size() const { return vec.size(); }
  bool empty() const { return vec.empty(); }
};

}  // namespace ds
}  // namespace x4444
