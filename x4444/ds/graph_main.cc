#include "x4444/ds/graph.h"
#include <iostream>

template <typename T>
struct Printer {
  void operator()(const T& v) const { std::cerr << v << ","; }
};

int main() {
  x4444::ds::Graph g;
  g.push_back({1, 2});           // 0
  g.push_back({0, 2, 3, 7});     // 1
  g.push_back({0, 1, 4, 5, 7});  // 2
  g.push_back({1, 4, 6, 7});     // 3
  g.push_back({2, 3, 7});        // 4
  g.push_back({2});              // 5
  g.push_back({3, 8});           // 6
  g.push_back({1, 2, 3, 4});     // 7
  g.push_back({6});              // 8

  std::cerr << "BFS(3):" << std::endl;
  g.bfs(3, Printer<int>());
  std::cerr << std::endl;
  std::cerr << "BFS2(3):" << std::endl;
  g.bfs2(3, Printer<int>());
  std::cerr << std::endl;

  const char * s = "Node";
  std::cerr << "BFS(3):" << std::endl;
  g.bfs(3, [s](int v) { std::cerr << s << ":" << v << ","; });
  std::cerr << std::endl;
  std::cerr << "BFS2(3):" << std::endl;
  g.bfs2(3, [s](int v) { std::cerr << s << ":" << v << ","; });
  std::cerr << std::endl;
  std::cerr << "DFS Preorder:" << std::endl;
  g.dfs_preorder(0, [](int v) { std::cerr << v << ","; });
  std::cerr << std::endl;
  std::cerr << "DFS Postorder:" << std::endl;
  g.dfs_postorder(0, [](int v) { std::cerr << v << ","; });
  std::cerr << std::endl;
}
