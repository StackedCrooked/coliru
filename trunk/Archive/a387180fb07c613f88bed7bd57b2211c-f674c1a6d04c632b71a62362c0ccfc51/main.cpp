#include <algorithm> // std::swap
#include <iostream>

class Foo
{
public:
  Foo()
    : x_(new int(5))
  {
    std::cout << "Foo::Foo(): x points to " << x_ << std::endl;
  }
  
  Foo(const Foo& rhs)
    : x_(new int(*rhs.x_))
  {
    std::cout << "Foo::Foo(const& Foo): x points to " << x_ << std::endl;
  }
  
  Foo& operator=(Foo rhs)
  {
    using std::swap;
    swap(x_, rhs.x_);
    return *this;
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
  Foo f2 = f;
}