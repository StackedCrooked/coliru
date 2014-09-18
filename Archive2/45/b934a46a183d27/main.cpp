#include <memory>

class X;

struct X {
  X() {}
};


int main()
{
  X x;
  (void)(x);
}