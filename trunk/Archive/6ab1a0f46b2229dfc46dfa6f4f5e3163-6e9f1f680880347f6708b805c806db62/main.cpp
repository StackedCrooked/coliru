#include <iostream>

struct B { 
  union U {
    struct S {} s;
    int i = 100;
  }
  u;  
};

int main()
{

}
