#include "x4444/ds/tree.h"
#include <iostream>

int main() {
  using Tree = x4444::ds::Tree<int>;
  using Node = Tree::Node;
  Tree t;
  t.root = new Node(5);
  t.root->left = new Node(15);
  t.root->right = new Node(30);
  t.root->left->left = new Node(20);
  t.root->left->right = new Node(25);
  t.root->right->left = new Node(35);
  t.root->right->right = new Node(50);

  std::cerr << "DFS Inorder:" << std::endl;
  t.dfs_inorder([](Node* n) { std::cerr << n->value << ","; });
  std::cerr << std::endl;
  std::cerr << "DFS Preorder:" << std::endl;
  t.dfs_preorder([](Node* n) { std::cerr << n->value << ","; });
  std::cerr << std::endl;
  std::cerr << "DFS Postorder:" << std::endl;
  t.dfs_postorder([](Node* n) { std::cerr << n->value << ","; });
  std::cerr << std::endl;
  std::cerr << "BFS Level-Order:" << std::endl;
  t.bfs([](Node* n) { std::cerr << n->value << ","; });
  std::cerr << std::endl;
}
