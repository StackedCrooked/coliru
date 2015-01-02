#include <iostream>
#include <array>

class myclass {
  public:
  virtual int myfunc1(void) {;}
  void myfunc2(void) {
    std::cout << myfunc1();  
  }
  private:
  int a {5};
};

class myclass2 : public myclass {
  public:
  int myfunc1(void) {
    return a;   
  }
  private:
  int a {6};
};

int main(void) {
  myclass2 A;
  A.myfunc2();   
}