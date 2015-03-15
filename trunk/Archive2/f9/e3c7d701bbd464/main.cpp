#include <set>
class B;
void f(B* b);

class B {
public:
  B() {}
  virtual ~B() { f(this); }
};

class D : public B { public: D() {} };

std::set<D*> ds;

void f(B* b) {
  D* d = static_cast<D*>(b);  // UB or subobject of type D?
  ds.erase(d);
}

int main(){
    D d;
    ds.insert(&d);
}
