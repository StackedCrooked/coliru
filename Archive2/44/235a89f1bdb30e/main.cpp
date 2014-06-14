#include <iostream>

struct A
{
  A(int i) { std::cout<<"Cstr "<< i<<'\n'; p = new int(i); }
 ~A()      { std::cout<<"Dstr "<<*p<<'\n'; delete p;       }

  const A& thiz() const { return *this; }

  int *p;
};

const A& constref( const A& a )
{
  return a;
}

int main()
{
  const A& a4 = A(4);
  const A& a5 = A(5).thiz();
  const A& a6 = constref( A(6) );

  std::cout << "a4 = "<< *a4.p <<'\n';
  std::cout << "a5 = "<< *a5.p <<'\n';
  std::cout << "a6 = "<< *a6.p <<'\n';
}

