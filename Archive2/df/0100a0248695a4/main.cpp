#include <set>
#include <iostream>
class B;
void f(B* b);

class B {
public:
  B() {}
  virtual void g() {}
  ~B() { f(this); }
};

class D : public B { public: D() {a = 0;} int a; };

std::set<D*> ds;

void f(B* b) {
  D* d = static_cast<D*>(b);  // UB or subobject of type D?
  ds.erase(d);
  std::cout << d->a << std::endl;
}

int main(){
    D d;
    ds.insert(&d);
}