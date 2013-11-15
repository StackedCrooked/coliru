#include <iostream>

struct tag {
  unsigned tagType; //or enum
  /* data */
  int i;
};

struct tagVisitor {
  template <class C> 
  void visitContainer(C& c) {
    for (auto& e : c) {
      visit(e);
    }
  }
  
  void visit(tag& t) {
    switch (t.tagType) {
    case 0: visit0(t); break;
    case 1: visit1(t); break;
    default:;
    }
  }
  
  virtual void visit0(tag& t) = 0;
  virtual void visit1(tag& t) = 0;
};

struct writeTagTypeToI : tagVisitor {
  virtual void visit0(tag& t) {t.i = 0;}
  virtual void visit1(tag& t) {t.i = 1;}
};    

struct echoI : tagVisitor {
  virtual void visit0(tag& t) { std::cout << "Got a zero: " << t.i << "\n";}
  virtual void visit1(tag& t) { std::cout << "Got a one: " << t.i << "\n";}
};    

#include <vector>

int main() {
  std::vector<tag> tags {{1,-1},{0,-1},{1,-1}}  ;
  writeTagTypeToI wti;
  echoI ei;
  
  wti.visitContainer(tags);
  ei.visitContainer(tags);
}
