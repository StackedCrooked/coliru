#include <iostream>

class Foo
{
public:
  Foo()
    : x_(new int(5))
  {
    std::cout << "Foo::Foo(): x points to " << x_ << std::endl;
  }
  
  ~Foo()
  {
    std::cout << "Foo::~Foo(): deleting x at " << x_ << std::endl;
    delete x_;
  }
private:
  int* x_;
};

void bad_method(Foo f)
{
}

int main()
{
  Foo f;
  bad_method(f);
}