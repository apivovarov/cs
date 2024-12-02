#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Graph {
  struct Node {
    Node(size_t _id, float _dist_from_src)
        : id(_id), dist_from_src(_dist_from_src) {}
    size_t id;
    float dist_from_src;
    bool operator<(const Node& other) const {
      return dist_from_src < other.dist_from_src;
    }
    bool operator>(const Node& other) const {
      return dist_from_src > other.dist_from_src;
    }
  };

  struct Edge {
    // id - Edge to id
    // distance - distance to id
    Edge(size_t _id, float _dist) : id(_id), distance(_dist) {}
    size_t id;
    float distance;
  };

  // adjustment edges.
  // outer vector index - source node
  // Edge id - dest node
  // Edge distance - distance btw src and dest nodes
  std::vector<std::vector<Edge>> adj;
  Graph(size_t sz) { adj.resize(sz); }
  size_t size() const { return adj.size(); }
  void add_edge(size_t from, size_t to, float dist) {
    adj[from].push_back({to, dist});
    adj[to].push_back({from, dist});
  }

  std::vector<float> dijkstra(size_t src_id) const {
    // vector index - node id
    // float value - distance from source node to destination (node id)
    std::vector<float> dist(size(), std::numeric_limits<float>::infinity());
    std::priority_queue<Graph::Node, std::vector<Graph::Node>,
                        std::greater<Graph::Node>>
        pq;
    pq.push({src_id, 0});
    dist[src_id] = 0;

    while (!pq.empty()) {
      const Graph::Node curr_node = pq.top();
      pq.pop();
      const size_t curr_id = curr_node.id;
      const float best_curr_dist = dist[curr_id];
      // Skip stale nodes (tasks) (if we already have a better path)
      if (curr_node.dist_from_src > best_curr_dist) continue;
      for (const Graph::Edge& edge : adj[curr_id]) {
        float newDist = best_curr_dist + edge.distance;
        if (newDist < dist[edge.id]) {
          dist[edge.id] = newDist;
          pq.push({edge.id, newDist});
        }
      }
    }
    return dist;
  }
};

int main() {
  Graph gr(7);
  gr.add_edge(1, 2, 7.0);
  gr.add_edge(2, 4, 15.0);
  gr.add_edge(4, 5, 6.0);
  gr.add_edge(5, 6, 9.0);
  gr.add_edge(6, 1, 14.0);
  gr.add_edge(1, 3, 9.0);
  gr.add_edge(2, 3, 10.0);
  gr.add_edge(4, 3, 11.0);
  gr.add_edge(6, 3, 2.0);

  std::vector<float> res = gr.dijkstra(1);

  std::cout << std::setw(4) << "Node"
            << ":" << std::setw(8) << "Dist" << std::endl;
  std::cout << "-------------" << std::endl;
  for (size_t id = 0; id < res.size(); ++id) {
    std::cout << std::setw(4) << id << ":" << std::setw(8) << std::fixed
              << std::setprecision(2) << res[id] << std::endl;
  }
}
