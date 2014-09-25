#include <iostream>

class Base {
public:
  virtual ~Base() {}
  virtual void world() const { std::cout << "Base" << std::endl; }
};

class DerivedA : public Base {
public:
  virtual ~DerivedA() {}
  void world() const { std::cout << "DerivedA" << std::endl; }
};

class DerivedB : public Base {
public:
  virtual ~DerivedB() {}
  void world() const  { std::cout << "DerivedB" << std::endl; }
};

class DerivedC : public Base {
public:
  virtual ~DerivedC() {}
  using Base::world;
};

class Test {
public:
  void world( DerivedA *instance ) { instance->world(); }
  void world( DerivedB *instance ) { instance->world(); }
  void world( Base     *instance ) { instance->world(); }
};

int main() {
  Base *a = new Base;
  Base *b = new DerivedA;
  Base *c = new DerivedB;
  Base *d = new DerivedC;
  
  Test hello;
  hello.world(a);
  hello.world(b);
  hello.world(c);
  hello.world(d);
}