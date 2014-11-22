#include <iostream>

struct Child1{
  void start() { std::cout << "Start Child1\n"; }    
};
struct Child2{
  void start() { std::cout << "Start Child2\n"; }    
};
struct Child3{
  void start() { std::cout << "Start Child3\n"; }    
};

template<typename Child>
void start() {
  auto child = Child();
  child.start();
}    

int main(int /*argc*/, char* argv[]) {
  auto type = std::string(argv[1]);
  if (type == "CHILD1")
      start<Child1>();
  else if (type == "CHILD2")
      start<Child2>();
  else if (type == "CHILD3")
      start<Child3>();
}
