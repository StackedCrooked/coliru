#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Base {
  std::unique_ptr<int> sp;
protected:
  ~Base() {};
public:
  Base(int) {}
  Base(Base const&) = default;
  Base(Base &&) = default;
  Base& operator=(Base const&) = default;
  Base& operator=(Base&&) = default;
};

struct Derived : Base {
  Derived() : Base(42) {}   
};

int main()
{
  Derived d;    
}
