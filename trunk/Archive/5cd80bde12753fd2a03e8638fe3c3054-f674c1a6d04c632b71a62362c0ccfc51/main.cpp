#include <algorithm> // std::swap
#include <iostream>

class Foo
{
private:
  int* x_;
  
  friend void swap(Foo& lhs, Foo& rhs)
  {
    std::cout << "in Foo::swap" << std::endl;
    using std::swap;
    swap(lhs.x_, rhs.x_);
  }
};

int main()
{
  Foo f1, f2;
  using std::swap;
  swap(f1, f2);
}