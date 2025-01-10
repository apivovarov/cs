#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

// 399. Evaluate Division
// Union-Find approach
class Solution {
  std::unordered_map<std::string, std::string> parent;
  std::unordered_map<std::string, double> weights;

  std::string getTrueParent(const std::string& node) {
    std::string par = parent.at(node);
    if (par == node) return node;
    const std::string& par2 = getTrueParent(par);
    if (par == par2) return par2;
    parent[node] = par2;
    weights[node] *= weights.at(par);
    return par2;
  }

  void unite(const std::string& a, const std::string& b, double w) {
    const std::string p0 = getTrueParent(a);
    const std::string p1 = getTrueParent(b);

    if (p0 != p1) {
      parent[p0] = p1;
      weights[p0] = w * weights[b] / weights[a];
    }
  }

 public:
  std::vector<double> calcEquation(
      const std::vector<std::vector<std::string>>& equations,
      const std::vector<double>& values,
      const std::vector<std::vector<std::string>>& queries) {
    if (equations.empty() || queries.empty()) return {};

    for (int i = 0; i < equations.size(); ++i) {
      auto& vv = equations[i];
      parent.try_emplace(vv[0], vv[0]);
      weights.try_emplace(vv[0], 1.0);
      parent.try_emplace(vv[1], vv[1]);
      weights.try_emplace(vv[1], 1.0);
      unite(vv[0], vv[1], values[i]);
    }

    std::vector<double> res;

    for (int i = 0; i < queries.size(); ++i) {
      auto& vv = queries[i];

      if (parent.find(vv[0]) == parent.end() ||
          parent.find(vv[1]) == parent.end() ||
          getTrueParent(vv[0]) != getTrueParent(vv[1])) {
        res.push_back(-1.0);
        continue;
      }

      double w0 = weights.at(vv[0]);
      double w1 = weights.at(vv[1]);
      res.push_back(w0 / w1);
    }

    return res;
  }
};

// 399. Evaluate Division
// DFS approach
class Solution2 {
 public:
  inline std::unordered_map<std::string,
                            std::vector<std::pair<std::string, double>>>
  makeAdj(const std::vector<std::vector<std::string>>& equations,
          const std::vector<double>& values) {
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>
        adj;
    for (int i = 0; i < equations.size(); ++i) {
      auto& vv = equations[i];
      adj[vv[0]].push_back({vv[1], values[i]});
      adj[vv[1]].push_back({vv[0], 1.0 / values[i]});
    }
    return adj;
  }

  bool visit(const std::string& node_id, double node_val,
             const std::string& target,
             const std::unordered_map<
                 std::string, std::vector<std::pair<std::string, double>>>& adj,
             std::unordered_map<std::string, double>& visited) {
    if (visited.count(node_id) > 0) return false;
    visited.emplace(node_id, node_val);
    if (node_id == target) return true;
    for (const std::pair<std::string, double>& pa : adj.at(node_id)) {
      const auto& neib = pa.first;
      auto neibV = node_val * pa.second;
      if (visit(neib, neibV, target, adj, visited)) return true;
    }
    return false;
  }

  double eval(
      const std::string& a, const std::string& b,
      const std::unordered_map<
          std::string, std::vector<std::pair<std::string, double>>>& adj) {
    if (adj.count(a) == 0 || adj.count(b) == 0) return -1.0;
    if (a == b) return 1.0;
    std::unordered_map<std::string, double> visited;
    if (visit(a, 1.0, b, adj, visited)) {
      return visited.at(b);
    }
    return -1.0;
  }

  std::vector<double> calcEquation(
      const std::vector<std::vector<std::string>>& equations,
      const std::vector<double>& values,
      const std::vector<std::vector<std::string>>& queries) {
    if (equations.empty()) return {};
    auto adj = makeAdj(equations, values);
    std::vector<double> res;
    for (const std::vector<std::string>& q : queries) {
      double v = eval(q[0], q[1], adj);
      res.push_back(v);
    }
    return res;
  }
};

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

bool compareRtol(double a, double b) {
  double rtol = 1e-4;
  const double small_number = 1e-9;  // Small constant to avoid division by zero
  return std::fabs(a - b) <=
         rtol * std::max({std::fabs(a), std::fabs(b), small_number});
}

void test(const std::vector<std::vector<std::string>>& equations,
          const std::vector<double>& values,
          const std::vector<std::vector<std::string>>& queries,
          const std::vector<double>& expected) {
  Solution sol;
  std::vector<double> res = sol.calcEquation(equations, values, queries);
  if (res.size() != expected.size() ||
      !std::equal(res.begin(), res.end(), expected.begin(), compareRtol)) {
    std::cerr << "ERROR: res: " << res << ", expected: " << expected
              << std::endl;
  }
}

int main() {
  test({{"a", "b"}, {"b", "c"}}, {2.0, 3.0},
       {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}},
       {6.0, 0.5, -1.0, 1.0, -1.0});

  test({{"a", "b"}, {"b", "c"}, {"bc", "cd"}}, {1.5, 2.5, 5.0},
       {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}},
       {3.75000, 0.40000, 5.00000, 0.2});

  test({{"a", "b"}}, {0.5}, {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}},
       {0.50000, 2.00000, -1.00000, -1.00000});

  test({{"a", "b"}, {"b", "c"}, {"c", "d"}}, {2.0, 3.0, 4.0},
       {{"a", "d"}, {"d", "a"}, {"b", "d"}, {"a", "b"}},
       {24.0, 1. / 24.0, 12.0, 2.0});
  test({{"x", "y"}}, {0.5}, {{"y", "x"}, {"x", "x"}, {"y", "y"}},
       {2.0, 1.0, 1.0});

  test({{"x1", "x2"}, {"x2", "x3"}, {"x1", "x4"}, {"x2", "x5"}},
       {3.0, 0.5, 3.4, 5.6},
       {{"x2", "x4"},
        {"x1", "x5"},
        {"x1", "x3"},
        {"x5", "x5"},
        {"x5", "x1"},
        {"x3", "x4"},
        {"x4", "x3"},
        {"x6", "x6"},
        {"x0", "x0"}},
       {1.13333, 16.80000, 1.50000, 1.00000, 0.0595238, 2.26667, 0.441176,
        -1.00000, -1.00000});
}
