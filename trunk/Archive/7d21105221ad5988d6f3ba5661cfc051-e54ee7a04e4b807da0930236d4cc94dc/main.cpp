#include <iostream>
#include <type_traits>

using std::ostream;

enum class A{a1, a2, a3};

template <class T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
ostream& operator<<(ostream& out, const T& a)
{
  switch(a)
    {
    case T::a1 :
      return out<<"a1";
    case T::a2 :
      return out<<"a2";
    case T::a3 :
      return out<<"a3";
    };
  return out;
}

int main()
{
  A a = A::a3;
  std::cout<<a<<std::endl;
}
