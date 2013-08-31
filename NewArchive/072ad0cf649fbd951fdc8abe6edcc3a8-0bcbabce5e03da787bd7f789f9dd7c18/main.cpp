#include <iostream>
class C{
 public:
   C(int) ;
   int f1(int);
   int f2(int);
   int (C::*f)(int);
};

int C::f1(int x){
   return -x ;
}

int C::f2(int x){
   return x;
}

C::C(int c){
  if (c<0){
    f = &C::f1 ;
   }
  else {
    f = &C::f2 ;
  }
}

int main()
{
}
