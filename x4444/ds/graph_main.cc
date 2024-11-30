#include "x4444/ds/graph.h"
#include <iostream>

template <typename T>
struct Printer {
  void operator()(const T& v) const { std::cerr << v << ","; }
};

int main() {
  x4444::ds::Graph g;
  g.push_back({1, 2});
  g.push_back({0, 2, 3});
  g.push_back({0, 1, 4});
  g.push_back({1, 4});
  g.push_back({2, 3});

  g.bfs(3, Printer<int>());
  std::cerr << std::endl;
  g.bfs2(3, Printer<int>());
  std::cerr << std::endl;

  const char * s = "Node";
  g.bfs(3, [s](int v) { std::cerr << s << ":" << v << ","; });
  std::cerr << std::endl;
  g.bfs2(3, [s](int v) { std::cerr << s << ":" << v << ","; });
  std::cerr << std::endl;
}
