#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>

struct ToNode {
  ToNode() = default;
  ToNode(size_t _id, float _dist) : id(_id), distance(_dist) {}
  size_t id;
  float distance;
  bool operator<(const ToNode& other) const {
    return distance < other.distance;
  }
  bool operator>(const ToNode& other) const {
    return distance > other.distance;
  }
};

struct Graph {
  std::vector<std::vector<ToNode>> adj;
  Graph(size_t sz) { adj.resize(sz); }
  size_t size() const { return adj.size(); }
  void add_egde(size_t from, size_t to, float dist) {
    adj[from].push_back({to, dist});
    adj[to].push_back({from, dist});
  }
};

std::vector<float> dijkstra(const Graph& gr, size_t src_id) {
  std::vector<size_t> visited(gr.size());
  std::vector<float> dist(gr.size(), std::numeric_limits<float>::infinity());
  std::priority_queue<ToNode, std::vector<ToNode>, std::greater<ToNode>> pq;
  ToNode src_node(src_id, 0);
  pq.push(src_node);
  dist[src_id] = 0;

  while (!pq.empty()) {
    const ToNode& curr_node = pq.top();
    pq.pop();
    const size_t curr_id = curr_node.id;
    visited[curr_id] = true;
    float const currDist = dist[curr_id];
    for (const ToNode& toNode : gr.adj[curr_id]) {
      if (visited[toNode.id]) continue;
      const float newDist = currDist + toNode.distance;
      if (newDist < dist[toNode.id]) {
        dist[toNode.id] = newDist;
        pq.push(toNode);
      }
    }
  }
  return dist;
}

int main() {
  Graph gr(7);
  gr.add_egde(1, 2, 7);
  gr.add_egde(2, 4, 15);
  gr.add_egde(4, 5, 6);
  gr.add_egde(5, 6, 9);
  gr.add_egde(6, 1, 14);
  gr.add_egde(1, 3, 9);
  gr.add_egde(2, 3, 10);
  gr.add_egde(4, 3, 11);
  gr.add_egde(6, 3, 2);

  std::vector<float> res = dijkstra(gr, 1);

  std::cout << std::setw(4) << "Node"
            << ":" << std::setw(6) << "Dist" << std::endl;
  std::cout << "-----------" << std::endl;
  for (size_t id = 0; id < res.size(); ++id) {
    std::cout << std::setw(4) << id << ":" << std::setw(6);
    std::cout << std::setw(6) << res[id];
    std::cout << std::endl;
  }
}
