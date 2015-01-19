#include <boost/optional.hpp>

struct A { 
  virtual int getInt() = 0; 
};

struct B : A {
  int getInt() { return 666; }
};

#include <iostream>

int main() {
  boost::optional<A&> maybeAnA;
  
  B b;
  maybeAnA = b; // non owning, just the reference
  
  boost::optional<A&> another(maybeAnA);
  
  std::cout << another->getInt();
}