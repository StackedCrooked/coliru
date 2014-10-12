#include <functional>
#include <memory>
#include <iostream>

struct Base {
  virtual void greet() { std::cout << "base\n"; }
};

struct Derived : public Base {
  virtual void greet() override { std::cout << "derived\n"; }
};

int main() {

std::unique_ptr<Base> sb = std::make_unique<Derived>();
//   std::unique_ptr<Base> sb = std::unique_ptr<Derived>(new Derived);
sb->greet();
}