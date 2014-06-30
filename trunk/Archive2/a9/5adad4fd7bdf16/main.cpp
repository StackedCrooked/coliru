#include <iostream>

class Node {
  friend class Graph;
  //...
  std::size_t id;
  public:
  Node(std::size_t const _id) : id(_id) {}
  //...
};

class Graph {
 //...
 public:
 Graph(Node const &node) { std::cout << "Look! I can access input node its id is " << node.id << std::endl; }
 //...
};

int main() {
  Node n(1);
  Graph G(n);
}