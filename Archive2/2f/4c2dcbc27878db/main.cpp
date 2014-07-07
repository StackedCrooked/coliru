#include <cstring>
#include <iostream>
#include <utility>

struct Obj {
  char *Data;
  
  Obj(const char *D) {
    std::cout << "Default constructor called" << std::endl;
    Data = new char[std::strlen(D)];
    std::memcpy(Data, D, std::strlen(D));
  }
  Obj(const Obj &O) {
    std::cout << "Copy constructor called" << std::endl;
    Data = new char[std::strlen(O.Data)];
    std::memcpy(Data, O.Data, std::strlen(O.Data));
  }
  Obj(Obj &&O) {
    std::cout << "Move constructor called" << std::endl;
    Data = O.Data;
    O.Data = nullptr;
  }
  ~Obj() {
    delete [] Data;
  }
};

struct BadContainer {
  Obj O;
  
  BadContainer(Obj &&O) : O(O) {} // Calls the copy constructor
};

struct GoodContainer {
  Obj O;
  
  GoodContainer(Obj &&O) : O(std::move(O)) {} // Calls the copy constructor    
};

Obj get_rvalue_obj() { return Obj("This is data"); } // Calls the default constructor

int main() {
  BadContainer B(get_rvalue_obj());
  GoodContainer C(get_rvalue_obj());
}