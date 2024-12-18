#include <iostream>
#include <vector>
#include <utility>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& arr) {
  for (const int v : arr) os << v << ",";
  os << std::endl;
  return os;
}

bool _check(const std::vector<std::vector<int>>& adj, int n_id, int p_id,
            std::vector<bool>& visited) {
  int cnt = 0;
  if (visited[n_id]) return false;
  visited[n_id] = true;
  for (int neib : adj[n_id]) {
    if (neib == p_id) continue;
    if (++cnt > 2) return false;
    if (!_check(adj, neib, n_id, visited)) return false;
  }
  return true;
}

bool check(const std::vector<std::vector<int>>& adj, int n_id) {
  std::vector<bool> visited(adj.size());
  bool res = _check(adj, n_id, -1, visited);
  if (!res) return false;
  return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

int main() {
  std::vector<std::vector<int>> adj = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
  std::cerr << std::boolalpha << check(adj, 0) << std::endl;
}
