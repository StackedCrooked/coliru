#include <iostream>
#include <memory>
#include <vector>

template<class Child>
class Parent {
 private: 
  std::vector<std::unique_ptr<Child>> children_;
 protected:
  ~Parent() {}
 public:
  const Child* getChild(size_t child_number) const { 
    return children_.at(child_number).get(); 
  } 
  Child* getChild(size_t child_number) {
    return children_.at(child_number).get(); 
  } 
  size_t getNumberOfChildren() const {
    return children_.size();
  }
  void addChild(std::unique_ptr<Child> child) {
    children_.emplace_back(std::move(child));
  }
};

struct Node : Parent<Node> {
 private:
  std::string name_;
 public:
  Node(std::string name) : name_(std::move(name)) {}
  void print() const { std::cout << "Node: " << name_  << "\n";}
  void setName(const std::string& name) { name_ = name; }
  void wrong() const {
    //children_[0]->setName("Wrong"); // Not allowed
    //getChild(0)->setName("Wrong"); // Not allowed
  }
};

void printRecursive(const Node* node) {
  if (node) {
    node->print();
    for (size_t i=0; i!=node->getNumberOfChildren(); ++i)
      printRecursive(node->getChild(i)); 
  }
}

int main() {
  // Initialization
  Node root("Root");
  root.addChild(std::make_unique<Node>("Child 1"));
  root.addChild(std::make_unique<Node>("Child 2"));
  
  // "Computation" with pointer-to-const
  const Node* root_ptr = &root;
  printRecursive(root_ptr);
}
