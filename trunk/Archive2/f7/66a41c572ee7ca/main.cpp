#include <iostream>
#include <array>

template<int I>
struct Foo {
  constexpr Foo () = default;
  constexpr int get_data () const { return I; }
};

struct Obj : Foo<10> {
    Obj (int d) : dummy (d) { }
    int dummy;
};

int
main (int argc, char *argv[])
{
  Obj obj { 1 };
  std::array<int, obj.get_data ()> korv;
}