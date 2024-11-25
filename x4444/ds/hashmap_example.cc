#include <iostream>
#include <unordered_set>
#include <string>

struct X {
  int a, b, c;
  constexpr bool operator==(const X& other) const noexcept {
    return a == other.a && b == other.b && c == other.c;
  }
  friend std::ostream& operator<<(std::ostream& os, const X& x);
  friend struct X_hash;
  friend struct X_equal_to;
};

std::ostream& operator<<(std::ostream& os, const X& x) {
  os << "X(" << x.a << "," << x.b << "," << x.c << ")";
  return os;
};

struct X_hash {
  constexpr size_t operator()(const X& x) const noexcept {
    std::hash<int> hh;
    size_t h1 = hh(x.a);
    size_t h2 = hh(x.b) << 1;
    size_t h3 = hh(x.c) << 2;
    return h1 ^ h2 ^ h3;
  }
};

struct X_equal_to {
  constexpr bool operator()(const X& x0, const X& x1) const noexcept {
    return x0.a == x1.a && x0.b == x1.b && x0.c == x1.c;
  }
};

int main() {
  // func obj X_equal_to is optional since X has operator== defined
  std::unordered_set<X, X_hash, X_equal_to> ss;
  ss.insert(X{1, 2, 3});
  ss.insert(X{4, 5, 6});
  ss.insert(X{4, 2, 3});

  for (auto&& x : ss) {
    std::cerr << x << std::endl;
  }
  return 0;
}
