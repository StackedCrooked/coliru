#include <iostream>
#include <memory>
#include <vector>

template<class Node>
class NodeContainer {
 private: 
  std::vector<std::unique_ptr<Node>> nodes_;
 public:
  const Node* get(size_t node_number) const { 
    return nodes_.at(node_number).get(); 
  } 
  Node* get(size_t node_number) {
    return nodes_.at(node_number).get(); 
  } 
  size_t size() const {
    return nodes_.size();
  }
  void add(std::unique_ptr<Node> node) {
    nodes_.emplace_back(std::move(node));
  }
};

struct Node {
 private:
  NodeContainer<Node> children_;
  std::string name_;
 public:
  Node(std::string name) : name_(std::move(name)) {}
  void attach(std::unique_ptr<Node> node) { children_.add(std::move(node)); }
  void setName(const std::string& name) { name_ = name; }
    
  void printRecursive() const { 
    std::cout << "Node: " << name_  << "\n";
    for (size_t i=0; i!=children_.size(); ++i) {
      auto child = children_.get(i);
      if (child)
        child->printRecursive();
    }
  }
  
  void wrong() const {
    //children_.get(0)->setName("Wrong"); // Not allowed
  }
};

int main() {
  // Initialization
  Node root("Root");
  root.attach(std::make_unique<Node>("Child 1"));
  root.attach(std::make_unique<Node>("Child 2"));
  
  // "Computation" with pointer-to-const
  const Node* root_ptr = &root;
  root_ptr->printRecursive();
}