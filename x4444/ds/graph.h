#include <vector>
#include <queue>

namespace x4444 {
namespace ds {

class Graph {
 protected:
  std::vector<std::vector<int>> adjList;

 public:
  void push_back(const std::vector<int>& adj) { adjList.push_back(adj); }
  void push_back(std::vector<int>&& adj) { adjList.push_back(adj); }

  template <typename Callable>
  void bfs(int root, Callable func) {
    std::queue<int> q;
    std::vector<bool> visited(adjList.size());
    q.push(root);

    while (!q.empty()) {
      const int& el = q.front();
      q.pop();
      if (visited[el]) continue;
      func(el);
      visited[el] = true;
      for (int n : adjList[el]) {
        q.push(n);
      }
    }
  }

  void bfs2(int root, std::function<void(int)> func) {
    std::queue<int> q;
    std::vector<bool> visited(adjList.size());
    q.push(root);

    while (!q.empty()) {
      const int& el = q.front();
      q.pop();
      if (visited[el]) continue;
      func(el);
      visited[el] = true;
      for (int n : adjList[el]) {
        q.push(n);
      }
    }
  }

  template <typename Callable>
  void __dfs_preorder(int n, std::vector<bool>& visited, Callable func) {
    if (visited[n]) return;
    visited[n] = true;
    func(n);
    for (auto ch : adjList[n]) {
      __dfs_preorder(ch, visited, func);
    }
  }

  template <typename Callable>
  void dfs_preorder(int src_node, Callable func) {
    std::vector<bool> visited(adjList.size());
    __dfs_preorder(src_node, visited, func);
  }

  template <typename Callable>
  void __dfs_postorder(int n, std::vector<bool>& visited, Callable func) {
    if (visited[n]) return;
    visited[n] = true;
    for (auto ch : adjList[n]) {
      __dfs_postorder(ch, visited, func);
    }
    func(n);
  }

  template <typename Callable>
  void dfs_postorder(int src_node, Callable func) {
    std::vector<bool> visited(adjList.size());
    __dfs_postorder(src_node, visited, func);
  }
};

}  // namespace ds
}  // namespace x4444
