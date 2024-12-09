#include <string>
#include <iostream>

class Solution {
 protected:
  bool _add_node(const std::vector<std::vector<int>>& adjs, int nid, int pid,
                 std::vector<bool>& visited) {
    // check if already visited
    if (visited[nid]) return false;
    visited[nid] = true;
    int ch_cnt = 0;
    for (int id : adjs[nid]) {
      if (id == pid) continue;
      if (++ch_cnt > 2) return false;
      if (!_add_node(adjs, id, nid, visited)) return false;
    }
    return true;
  }

 public:
  // Validates the following conditions:
  // - No node has more than 2 children
  // - The graph contains no cycles
  // - All nodes are connected (no disconnected components)
  bool isBinaryTree(const std::vector<std::vector<int>>& adjs, int root) {
    if (adjs.empty()) return true;
    if (adjs.size() == 1 && adjs[0].empty()) return true;
    std::vector<bool> visited(adjs.size());
    if (!_add_node(adjs, root, -1, visited)) return false;
    // check if all visited
    for (bool v : visited) {
      if (!v) return false;
    }
    return true;
  }
};

void test(const std::vector<std::vector<int>>& adjs, int root, bool expected) {
  Solution sol;
  bool res = sol.isBinaryTree(adjs, root);
  if (res != expected)
    std::cerr << std::boolalpha << "ERROR: res: " << res
              << ", expected: " << expected << std::endl;
}

int main() {
  test({}, 0, true);
  test({{}}, 0, true);
  test({{1, 2}, {0}, {0}}, 0, true);
  test({{1, 2}, {0}, {0}}, 1, true);
  test({{1, 2}, {0}, {0}}, 2, true);
  test({{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}}, 0, true);
  test({{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}}, 1, false);
  test({{1, 2}, {0, 3, 4}, {0, 5}, {1, 4}, {1, 3}, {2}}, 0, false);
  test({{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}, {7}, {6}}, 0, false);
}