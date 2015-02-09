#include <iostream>

struct A { 
  virtual void f () { std::cerr << "A::f()\n";}
  virtual void g () { std::cerr << "A::f()\n";}
};

struct B { 
  virtual void g () { std::cerr << "B::f()\n";}
};

struct C : A, B { 
  virtual void g () { std::cerr << "B::f()\n";}
};

int main () {
  C c;
  
  A * a_p = &c; 
  B * b_p = reinterpret_cast<B*> (a_p); // DANGER DANGER

  b_p->g ();                            // OH FUCK
}