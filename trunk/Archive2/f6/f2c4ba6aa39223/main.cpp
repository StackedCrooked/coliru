#include <vector>
#include <memory>
#include <iostream>

class Node {
 private:
  std::vector<std::unique_ptr<Node>> children_{};
 public:
  virtual      ~Node() {}
  
  size_t       getNumChildren() const { return children_.size(); }
  const Node*  getChild(size_t child_num) const { return children_.at(child_num).get(); }
  Node*        getChild(size_t child_num) { return children_.at(child_num).get(); }
  void         addChild(std::unique_ptr<Node> child) { children_.emplace_back(std::move(child)); }
  
  virtual void print() const = 0;
};

class PrintNode : public Node {
 private:
  std::string name_;
 public:
  PrintNode(std::string name) : name_(std::move(name)) {}
  void print() const override { std::cout << "PrintNode: " << name_ << "\n"; }
  void setName(const std::string& name) { name_ = name; }
};

void printRecursive(const Node* node) {
  if (node) {
    node->print();
    for (size_t i = 0; i != node->getNumChildren(); ++i)
      printRecursive(node->getChild(i)); 
  }
}

int main() {
  // Initialization
  PrintNode root("Root");
  root.addChild(std::make_unique<PrintNode>("Child 1"));
  root.addChild(std::make_unique<PrintNode>("Child 2"));
  
  // Computation with pointer-to-const
  const PrintNode* root_ptr = &root;
  printRecursive(root_ptr);
}
