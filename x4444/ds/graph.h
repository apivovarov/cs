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
};

}  // namespace ds
}  // namespace x4444
