#include <iostream>
#include <utility>

struct Obj {
  Obj() { std::cout << "Default constructor called" << std::endl; }
  Obj(const Obj &) { std::cout << "Copy constructor called" << std::endl; }
  Obj(Obj &&) { std::cout << "Move constructor called" << std::endl; }  
};

struct BadContainer {
  Obj O;
  
  BadContainer(Obj &&O) : O(O) {} // Calls the copy constructor
};

struct GoodContainer {
  Obj O;
  
  GoodContainer(Obj &&O) : O(std::move(O)) {} // Calls the copy constructor    
};

Obj get_rvalue_obj() { return Obj(); } // Calls the default constructor

int main() {
  BadContainer B(get_rvalue_obj());
  GoodContainer C(get_rvalue_obj());
}