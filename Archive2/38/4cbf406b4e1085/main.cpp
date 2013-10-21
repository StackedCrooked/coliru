#include <iostream> 

class A { 
  public: void func () { std::cerr << "A::v -> " << v; }
  private: int v;
};

struct B { 
  int v;
};

union AB {
  A a;
  B b;
};

int
main (int argc, char *argv[])
{
  AB ab; 

  ab.b.v = 123;
  ab.a.func (); 
}