#include <iostream>

class A {
public:
  virtual void decompose() = 0;
  virtual ~A() {
      std::cout << "~A";
  }
};
class B:public A {
private:
  int *b_data;
public:
  void decompose() {
      std::cout << "B_decompose"; if (b_data != NULL) delete [] b_data;
  }
  ~B() { std::cout << "~B";}
};

class C:public A {
private:
  int *c_data;
public:
  void decompose() {
      std::cout << "C_decompose"; if (c_data != NULL) delete [] c_data;
  }
  ~C() { std::cout << "~C";}
};
   int main(int argc, char** argv) {
       B b;
       C c;
        A* p = &b;
        p->decompose();
        p = &c;
        p->decompose();
        return 0;
    }