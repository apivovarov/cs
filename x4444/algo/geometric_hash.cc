#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>

using V = std::pair<float, float>;

namespace std {
template <>
struct hash<V> {
  hash<float> hh;
  std::uint64_t operator()(const V& v) {
    auto h0 = hh(v.first);
    auto h1 = hh(v.second);
    return h0 ^ (h1 << 1);
  }
};
}  // namespace std

std::ostream& operator<<(std::ostream& os, V v) {
  std::cout << "[" << v.first << "," << v.second << "]";
}

V get_hash(V a, V b, V c) {
  float scale;
  scale = 2 / std::sqrt((a.first - b.first) * (a.first - b.first) +
                        (a.second - b.second) * (a.second - b.second));

  float x0 = a.first + (b.first - a.first) / 2;
  float y0 = a.second + (b.second - a.second) / 2;

  float x1 = a.first - x0;
  float y1 = a.second - y0;

  float x2 = b.first - x0;
  float y2 = b.second - y0;

  float x3 = c.first - x0;
  float y3 = c.second - y0;

  x1 *= scale;
  y1 *= scale;
  x2 *= scale;
  y2 *= scale;
  x3 *= scale;
  y3 *= scale;

  float _cos = x1;
  float _sin = y1;

  float x1r = _cos * x1 + _sin * y1;
  float y1r = (-_sin) * x1 + _cos * y1;

  float x2r = _cos * x2 + _sin * y2;
  float y2r = (-_sin) * x2 + _cos * y2;

  float x3r = _cos * x3 + _sin * y3;
  float y3r = (-_sin) * x3 + _cos * y3;

  return {x3r, y3r};
}

std::unordered_map<V, V> make_ghash(const std::vector<V>& vers) {
  std::unordered_map<V, V> map(vers.size());

  return map;
}

int main() {
  std::vector<V> v = {{5, 4}, {1, 1}, {2, 8}};

  V v0 = get_hash(v[0], v[1], v[0]);
  std::cout << v0 << std::endl;

  V v1 = get_hash(v[0], v[1], v[1]);
  std::cout << v1 << std::endl;

  V v2 = get_hash(v[0], v[1], v[2]);
  std::cout << v2 << std::endl;

  V v22 = get_hash(v[1], v[0], v[2]);
  std::cout << v22 << std::endl;
}
