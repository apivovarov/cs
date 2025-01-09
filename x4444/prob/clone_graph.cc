#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Definition for a Node.
class Node {
 public:
  int val;
  std::vector<Node*> neighbors;
  Node() {
    val = 0;
    neighbors = std::vector<Node*>();
  }
  Node(int _val) {
    val = _val;
    neighbors = std::vector<Node*>();
  }
  Node(int _val, const std::vector<Node*>& _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

// 133. Clone Graph
class Solution {
 public:
  void visit(Node* node, std::unordered_map<Node*, Node*>& visited) {
    if (!node || visited.count(node) > 0) return;
    visited.emplace(node, new Node(node->val));
    for (Node* neib : node->neighbors) {
      visit(neib, visited);
    }
  }

  Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    if (node->neighbors.empty()) return new Node(node->val);

    std::unordered_map<Node*, Node*> old_to_new;
    visit(node, old_to_new);

    for (auto& pa : old_to_new) {
      Node* n = pa.first;
      Node* n2 = pa.second;
      for (Node* neib : n->neighbors) {
        n2->neighbors.push_back(old_to_new.at(neib));
      }
    }
    return old_to_new.at(node);
  }
};

Node* makeGraph(const std::vector<std::vector<int>>& adj, int rootV) {
  if (adj.empty()) return nullptr;
  if (adj.size() == 1 && adj[0].empty()) return new Node(1);
  std::vector<Node*> map;
  map.push_back(nullptr);  // dummy
  Node* root;
  for (int i = 1; i <= adj.size(); ++i) {
    map.push_back(new Node(i));
    if (i == rootV) {
      root = map.back();
    }
  }
  for (int i = 1; i <= adj.size(); ++i) {
    const std::vector<int>& neib = adj[i - 1];
    for (int nid : neib) {
      map[i]->neighbors.push_back(map[nid]);
    }
  }
  return root;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> arr) {
  os << "[";
  for (int i = 0; i < arr.size(); ++i) {
    if (i > 0) os << ",";
    os << arr[i];
  }
  os << "]";
  return os;
}

void walkGraph(Node* n, std::unordered_map<Node*, int>& visited) {
  if (!n) return;
  if (visited.count(n) > 0) return;
  visited.emplace(n, n->val);
  for (Node* neib : n->neighbors) {
    walkGraph(neib, visited);
  }
}

std::vector<std::vector<int>> makeAdj(Node* src) {
  if (!src) return {};
  if (src->neighbors.empty()) return {{}};
  std::unordered_map<Node*, int> map;
  walkGraph(src, map);

  std::vector<std::vector<int>> adj(map.size());
  for (const auto& pa : map) {
    Node* n = pa.first;
    int id = pa.second;
    for (Node* neib : n->neighbors) {
      int neibId = map.at(neib);
      adj[id - 1].push_back(neibId);
    }
    std::sort(adj[id - 1].begin(), adj[id - 1].end());
  }
  return adj;
}

void test_infra() {
  {
    Node* root = makeGraph({}, 1);
    if (root) std::cerr << "ERROR: Node * should be nullptr" << std::endl;
  }
  {
    Node* root = makeGraph({{}}, 1);
    if (!(root && root->neighbors.empty()))
      std::cerr << "ERROR: Node should have empty neighbors" << std::endl;
  }
  {
    std::vector<std::vector<int>> adj = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};
    Node* root = makeGraph(adj, 1);
    std::vector<std::vector<int>> adj2 = makeAdj(root);
    if (adj != adj2) {
      std::cerr << "ERROR: makeGraph / makeAdj missmatch" << std::endl;
    }
  }
}

void test(const std::vector<std::vector<int>>& adj) {
  Node* node = makeGraph(adj, 1);
  Solution sol;
  Node* node2 = sol.cloneGraph(node);

  std::vector<std::vector<int>> adj2 = makeAdj(node2);
  if (adj != adj2) {
    std::cerr << "ERROR: Graph clone is not the same" << std::endl;
  }
}

int main() {
  test_infra();
  test({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
  test({{}});
  test({});
}
