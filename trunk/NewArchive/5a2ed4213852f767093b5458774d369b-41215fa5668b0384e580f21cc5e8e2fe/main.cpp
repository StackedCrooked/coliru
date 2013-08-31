struct A {
  struct B {
    struct X;
  };
};

namespace B {
  extern A X;
}

struct A::B::X;