#include <list>
class B;
void f(B* b);

class B {
public:
  B() {}
  virtual ~B() { f(this); }
};

class D : public B { public: D() {} };

std::list<D*> ds;

void f(B* b) {
  for (std::list<D*>::iterator i = ds.begin(); i != ds.end(); ++i)
  {
    if (*i == b) { ds.erase(i); break; }
  }
  
  D* d = static_cast<D*>(b);
  
  for (std::list<D*>::iterator i = ds.begin(); i != ds.end(); ++i)
  {
    if (*i == d) { ds.erase(i); break; }
  }
}

int main(){
    D d;
    ds.push_back(&d);
}
