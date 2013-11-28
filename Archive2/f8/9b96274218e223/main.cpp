struct C{
   int val = 15;
};

struct B{
    C c;
    int k = 9;
};

struct A {
  template<typename T, typename OType, typename IType, OType T::* OField = nullptr, IType OType::* IField = nullptr>
  IType test(T& d){
    if (OField != nullptr && IField != nullptr) {
      return d.*OField.*IField; 
    }
    return 0;
  }
};

#include <iostream>

int main(int argc, char *argv[])
{

    A a;
    B be;

    std:: cout << a.test<B, C, int, &B::c, &C::val>(be) << '\n';
}
