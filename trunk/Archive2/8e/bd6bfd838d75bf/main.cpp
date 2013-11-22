#include <iostream>
#include <boost/unordered_set.hpp>

template<class T> struct EqualByValue {
  bool operator()(T const* a, T const* b) const { return *a == *b; }
};

struct Base {
  virtual bool operator==(Base const& other) const {
    std::cerr << "Base==" << std::endl;
  }
};

struct Derived : Base {
  bool operator==(Derived const& other) const override {
    std::cerr << "Derived==" << std::endl;
  }
};

int main(int argc, char** argv){
  typedef boost::unordered_set<Base*, boost::hash<Base*>, EqualByValue<Base> > 
    MySet;
  MySet s;
  Derived* d1 = new Derived();
  Derived* d2 = new Derived();
  s.insert(d1);
  s.insert(d2);
  s.find(d2);
  delete d1; delete d2; return 0;
}