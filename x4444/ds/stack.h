#include <vector>
#include <stdexcept>

namespace x4444 {
namespace ds {

template <typename T>
class Stack {
 protected:
  std::vector<T> vec;

 public:
  void push(const T& i) { vec.push_back(i); }
  void push(T&& i) { vec.push_back(std::forward<T>(i)); }
  void pop() {
    if (vec.empty()) throw std::out_of_range("Stack is empty");
    vec.pop_back();
  }
  T head() {
    if (vec.empty()) throw std::out_of_range("Stack is empty");
    return vec[vec.size() - 1];
  }
  size_t size() { return vec.size(); }
  bool empty() { return vec.empty(); }
};

}  // namespace ds
}  // namespace x4444
