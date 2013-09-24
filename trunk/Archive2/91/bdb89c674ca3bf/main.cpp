#include <iostream>

struct Obj {
  Obj() = default;

  Obj(Obj&&) {
    std::cerr << "move ";
  }

  Obj& operator= (Obj) {
    std::cerr << "move-operator= ";
    return *this;
  }
};

int
main (int argc, char *argv[])
{
  Obj o1;
  Obj o2;

  o1 = std::move (o2);
}