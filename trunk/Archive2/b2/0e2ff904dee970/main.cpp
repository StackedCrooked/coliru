#include <iostream>

class Machin{
public:
  Machin(int a) : a(a){
    std::cout<<(void*)p<<std::endl;   
  }
private:

  int  a;
  int* p;
};

int main(){
    Machin m;
}