#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

class A {
public:
  virtual void decompose() { std::cout << "A";}
  virtual ~A() {
    decompose();
  }
};

class B:public A {
private:
  int *b_data;
public:
  void decompose() {
      std::cout << "B";
    if (b_data != NULL) delete [] b_data;
  }
};

class C:public A {
private:
  int *c_data;

public:
  void decompose() {
      std::cout << "C";
    if (c_data != NULL) delete [] c_data;
  }
  ~C() {}
};
/*
 * 
 */
int main(int argc, char** argv) {
    B b;
    C c;
    return 0;
}