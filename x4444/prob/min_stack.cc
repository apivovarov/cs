#include <iostream>
#include <vector>
#include <limits>

class MinStack {
  std::vector<int> st;
  std::vector<int> mi;
  int min = std::numeric_limits<int>::max();

 public:
  MinStack() { mi.push_back(min); }

  void push(int val) {
    if (val < min) min = val;
    st.push_back(val);
    mi.push_back(min);
  }

  void pop() {
    st.pop_back();
    mi.pop_back();
    min = mi.back();
  }

  int top() { return st.back(); }

  int getMin() { return min; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

void test(const std::vector<std::string>& act,
          const std::vector<std::vector<int>>& params) {
  MinStack st;
}

int main() {
  MinStack st;
  st.push(-2);
  st.push(0);
  st.push(-3);

  std::cerr << st.top() << std::endl;
  std::cerr << st.getMin() << std::endl;
  st.pop();
  std::cerr << st.top() << std::endl;
  std::cerr << st.getMin() << std::endl;
  st.pop();
  std::cerr << st.top() << std::endl;
  std::cerr << st.getMin() << std::endl;
  st.pop();
}
